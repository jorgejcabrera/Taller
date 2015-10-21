/*
 * Server.cpp
 *
 *  Created on: 4 de oct. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/Server.h"

Server::Server(int port, GameController *myController) {
	this->port = port;
	this->serverSocket = 0;
	this->gController = myController;
	this->readQueue = new SocketQueue();
	this->lastReportedServer = time(0);
}

int Server::initSocketServer(){
	this->serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	if ( this->serverSocket < 0) {
		cout << "Error al crear el socket" << endl;
		return ERROR;
	}
	memset(&this->serverAddress, 0, sizeof(this->serverAddress));
	this->serverAddress.sin_family = AF_INET;
	this->serverAddress.sin_addr.s_addr = htons(INADDR_ANY);
	this->serverAddress.sin_port = htons(this->port);


	//int opt = 1;
	//setsockopt(this->serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

	//Bindeamos el socket
	if ( bind(this->serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0 ) {
		cout << "Error en la conexion bind.." << endl;
		return ERROR;
	}
	// Listen socket Clients
	if (listen(this->serverSocket, 2) < 0) {
		cout << "Error en el listen"<<endl;
		return ERROR;
	}
	return OK;
}

int Server::run(void * data){
	cout << "RUN" <<endl;
	//TODO: esto deberia ser while true?
	int cliente;
	socklen_t tamano = sizeof(serverAddress);
	while(true){
			if((cliente = accept(this->serverSocket,(struct sockaddr*)&serverAddress,&tamano))>0){

				Client *newClient = new Client(cliente, this->readQueue);
				readClientUserName(newClient);
				newClient->startCommunication();
				this->clients.insert(make_pair(newClient->getUserName(),newClient));

				//Cada vez que se conecta un cliente agrego un protagonista que tiene un owner
				this->gController->getJuego()->agregarProtagonista(newClient->getUserName());

				//Mando la dimension de la ventana
				newClient->writeMessagesInQueue(new Message("window","window", GameSettings::GetInstance()->getScreenWidth(),GameSettings::GetInstance()->getScreenHeight()));

				//Mando la informacion que está en el YAML
				newClient->writeMessagesInQueue(GameSettings::GetInstance()->getListMessageConfiguration());

				//Mando los tiles para dibujarlos en la vista
				newClient->writeMessagesInQueue(this->gController->getTilesMessages());

				//Mando las entidades que tiene el mapa
				newClient->writeMessagesInQueue(gController->getEntitiesMessages());

				//Mando los protagonistas hasta el momento
				newClient->writeMessagesInQueue(gController->getProtagonistasMessages());
			}
	}
	cout << "FIN RUN" <<endl;
	return 0;
}

void Server::processReceivedMessages(){
	this->readQueue->lockQueue();
	/* 1- Bajo todos los mansajes de la cola
	 * 2- actualizo la posicion de los protagonistas
	 * */
	//TODO revisar, hoy no usamos la lista idEntitiesUpdated porque notificamos lo que se este "moviendo"
	this->idEntitiesUpdated.clear();
	while(!this->readQueue->isEmpty()){
		Message* messageUpdate = this->readQueue->pullTailWithoutLock();
		if(messageUpdate->getTipo()=="ping"){
			/*stringstream ss;
			ss << "recibi ping del cliente: "<< messageUpdate->getNombre();
			Logger::get()->logDebug("Server","processReceivedMessages", ss.str());
			*/
			this->clients.at(messageUpdate->getNombre())->reporting();
		}else if(messageUpdate->getTipo()=="exit"){
			//TODO desconectar al cliente? hoy deberia hacerlo cuando no detecta novedades
			Logger::get()->logDebug("Server","processReceivedMessages", "RECIBI MESAJE DE DESCONEXION");
		}else{
			int idUpdate = messageUpdate->getId();
			this->gController->getJuego()->setDestinoProtagonista(idUpdate, messageUpdate->getPositionX(), messageUpdate->getPositionY());
			this->idEntitiesUpdated.push_back(idUpdate);
		}
	}
	this->readQueue->unlockQueue();
}

void Server::notifyClients(){
	map<int,EntidadDinamica*> protagonistas = this->gController->getJuego()->getProtagonistas();
	for(map<int,EntidadDinamica*>::iterator it=protagonistas.begin(); it!=protagonistas.end();++it){
		if (it->second->isWalking()){
			Message *messageUpdate = new Message(it->second->getId(), it->second->getScreenPosition()->first, it->second->getScreenPosition()->second);
			//Logger::get()->logDebug("Server","notifyClients",messageUpdate->toString());
			Logger::get()->logDebug("Server","notifyClients","ANTES 1");
			list<Client*> activeClients= getActiveClients();
			Logger::get()->logDebug("Server","notifyClients","DESPUES 1");
			for(list<Client*>::iterator clientIterator=activeClients.begin(); clientIterator!=activeClients.end(); ++clientIterator){
				(*clientIterator)->writeMessagesInQueue(messageUpdate);
			}
			/*for(map<string,Client*>::iterator clientIterator=this->clients.begin(); clientIterator!=this->clients.end(); ++clientIterator){
				clientIterator->second->writeMessagesInQueue(messageUpdate);
			}*/
			Logger::get()->logDebug("Server","notifyClients","FIN 1");
		}
	}
	//MANDO los nuevos personajes
	list<EntidadDinamica*> *nuevosProtagonistas = this->gController->getJuego()->getNewProtagonistasToNotify();
	for(list<EntidadDinamica*>::iterator it=nuevosProtagonistas->begin(); it!=nuevosProtagonistas->end();++it){
		Message *protagonistaMessage = new Message((*it)->getId(), DefaultSettings::getTypeEntity((*it)->getName()), (*it)->getName(), (*it)->getPosition()->first, (*it)->getPosition()->second);
		protagonistaMessage->setOwner((*it)->getOwner());
		list<Client*> activeClients= getActiveClients();
		for(list<Client*>::iterator clientIterator=activeClients.begin(); clientIterator!=activeClients.end(); ++clientIterator){
			if((*clientIterator)->getUserName()!=(*it)->getOwner()){
				//no notifico al dueño del personaje porque ya lo recibio
				(*clientIterator)->writeMessagesInQueue(protagonistaMessage);
			}
		}
	}
	this->gController->getJuego()->cleanNewProtagonistas();
	pingMessage();
}

void Server::pingMessage(){
	//Si hace mas de X segundos notifico que estoy conectado
	if((time(0)-this->lastReportedServer)>=(DefaultSettings::getTimeOut()-5)){
			Message* ping = new Message();
			ping->pingMessage("server");
			list<Client*> activeClients= getActiveClients();
			for(list<Client*>::iterator clientIterator=activeClients.begin(); clientIterator!=activeClients.end(); ++clientIterator){
				(*clientIterator)->writeMessagesInQueue(ping);
			}
			this->lastReportedServer = time(0);
		}
}

void Server::verifyClientsConections(){
	list<Client*> activeClients= getActiveClients();
	for(list<Client*>::iterator clientIterator=activeClients.begin(); clientIterator!=activeClients.end(); ++clientIterator){
		if((*clientIterator)->getTimeSinceLastReport()>= DefaultSettings::getTimeOut()){
			(*clientIterator)->disconect();
			stringstream ss;
			ss<< "CLIENTE se deconecto: "<< (*clientIterator)->getUserName();
			Logger::get()->logDebug("Server","verifyClientsConections",ss.str());
		}
	}
}

list<Client*> Server::getActiveClients(){
	list<Client*> activeClients;
	for(map<string,Client*>::iterator clientIterator=this->clients.begin(); clientIterator!=this->clients.end(); ++clientIterator){
		//cout <<"STATUS: "<< clientIterator->second->getStatus() << endl;
		if(clientIterator->second->getStatus()==0){
			activeClients.push_back(clientIterator->second);
		}
	}
	return activeClients;
}

Server::~Server() {
	for(map<string,Client*>::iterator it=this->clients.begin(); it!=this->clients.end(); ++it){
		it->second->~Client();
	}
	delete(this->readQueue);
	close(this->serverSocket);
}

void Server::readClientUserName(Client *newClient){
	bool validUserName=false;
	while(!validUserName){
		string userName=newClient->readUserName();
			Logger::get()->logDebug("Server","run",userName);
			map<string,Client*>::iterator it = this->clients.find(userName);
			if(it != this->clients.end()){
				Logger::get()->logDebug("Server","readClientUserName","YA EXISTE EL CLIENTE");
				newClient->responseUserName("FAIL");
			}else{
				newClient->responseUserName("OK");
				newClient->setUserName(userName);
				validUserName=true;
				Logger::get()->logDebug("Server","readClientUserName","NO EXISTE EL CLIENTE");
			}
	}
}
