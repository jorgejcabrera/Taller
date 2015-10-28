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
	this->gameSettings = GameSettings::GetInstance();
}

int Server::initSocketServer(){
	this->serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	if ( this->serverSocket < 0) {
		Logger::get()->logError("Server","initSocketServer","Error al crear el socket");
		return ERROR;
	}
	memset(&this->serverAddress, 0, sizeof(this->serverAddress));
	this->serverAddress.sin_family = AF_INET;
	this->serverAddress.sin_addr.s_addr = htons(INADDR_ANY);
	this->serverAddress.sin_port = htons(this->port);

	//Bindeamos el socket
	if ( bind(this->serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0 ) {
		Logger::get()->logError("Server","initSocketServer","Error en la conexion bind..");
		return ERROR;
	}
	// Listen socket Clients
	if (listen(this->serverSocket, 2) < 0) {
		Logger::get()->logError("Server","initSocketServer","Error en el listen");
		return ERROR;
	}

	this->isAlive = true;
	return OK;
}

void Server::shutDown(){
	this->isAlive = false;
}

bool Server::isRunning(){
	return this->isAlive;
}

int Server::run(void * data){
	//TODO: esto deberia ser while true?
	int cliente;
	socklen_t tamano = sizeof(serverAddress);
	while(this->isAlive){
			if((cliente = accept(this->serverSocket,(struct sockaddr*)&serverAddress,&tamano))>0){
				Client* newClient = new Client(cliente, this->readQueue);
				initConnection(newClient);

				//Mando la dimension de la ventana
				newClient->writeMessagesInQueue(new Message("window","window", GameSettings::GetInstance()->getScreenWidth(),GameSettings::GetInstance()->getScreenHeight(),  GameSettings::GetInstance()->getMapWidth(),  GameSettings::GetInstance()->getMapHeight()));
				//cout << "AMCHO: " << GameSettings::GetInstance()->getMapWidth() << "ALTO" <<GameSettings::GetInstance()->getMapHeight()<<endl;

				//Mando la informacion que está en el YAML
				newClient->writeMessagesInQueue(GameSettings::GetInstance()->getListMessageConfiguration());

				//Mando los tiles para dibujarlos en la vista
				newClient->writeMessagesInQueue(this->gController->getTilesMessages());

				//Mando las entidades que tiene el mapa
				newClient->writeMessagesInQueue(gController->getEntitiesMessages());

				//Mando los protagonistas hasta el momento
				newClient->writeMessagesInQueue(getProtagonistasMessages());
			}
	}
	return 0;
}


list<Message*> Server::getProtagonistasMessages(){
	list<Message*> listaDeProtagonistas;
			map<int,EntidadDinamica*> protagonistas = this->gController->getJuego()->getProtagonistas();
			for(map<int,EntidadDinamica*>::iterator it=protagonistas.begin(); it!=protagonistas.end();++it){
				string tipoEntidad = DefaultSettings::getTypeEntity((*it).second->getName());
				//0 : conectado, -1 Desconectado
				int clientConnected = this->clients.at((*it).second->getOwner())->getStatus();
				Message *protagonistaMessage = new Message((*it).second->getId(), tipoEntidad, (*it).second->getName(), (*it).second->getPosition()->first, (*it).second->getPosition()->second,clientConnected);
				protagonistaMessage->setOwner((*it).second->getOwner());
				listaDeProtagonistas.push_back(protagonistaMessage);
			}
			return listaDeProtagonistas;

}

void Server::processReceivedMessages(){
	this->readQueue->lockQueue();
	//TODO revisar, hoy no usamos la lista idEntitiesUpdated porque notificamos lo que se este "moviendo"
	this->idEntitiesUpdated.clear();
	while(!this->readQueue->isEmpty()){
		Message* messageUpdate = this->readQueue->pullTailWithoutLock();
		if(messageUpdate->getTipo()=="ping"){
			this->clients.at(messageUpdate->getNombre())->reporting();
		}else if(messageUpdate->getTipo()=="exit"){
			Logger::get()->logInfo("Server","processReceivedMessages", "RECIBI MESAJE DE DESCONEXION");
		} else {
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
		if (it->second->hasToNotify()){
			Message *messageUpdate = new Message(it->second->getId(), it->second->getPosition()->first, it->second->getPosition()->second);
			//messageUpdate->setAsNewPath(it->second->pathIsNew());
			list<Client*> activeClients= getActiveClients();
			for(list<Client*>::iterator clientIterator=activeClients.begin(); clientIterator!=activeClients.end(); ++clientIterator){
				(*clientIterator)->writeMessagesInQueue(messageUpdate);
			}
		}
	}
	//MANDO los nuevos personajes
	list<EntidadDinamica*> *nuevosProtagonistas = this->gController->getJuego()->getNewProtagonistasToNotify();
	for(list<EntidadDinamica*>::iterator it=nuevosProtagonistas->begin(); it!=nuevosProtagonistas->end();++it){
		int clientConnected = this->clients.at((*it)->getOwner())->getStatus();
		Message *protagonistaMessage = new Message((*it)->getId(), DefaultSettings::getTypeEntity((*it)->getName()), (*it)->getName(), (*it)->getPosition()->first, (*it)->getPosition()->second, clientConnected);
		protagonistaMessage->setOwner((*it)->getOwner());
		list<Client*> activeClients= getActiveClients();
		for(list<Client*>::iterator clientIterator=activeClients.begin(); clientIterator!=activeClients.end(); ++clientIterator){
			if((*clientIterator)->getUserName()!=(*it)->getOwner()){
				//no notifico al dueño del personaje porque ya lo recibio
				(*clientIterator)->writeMessagesInQueue(protagonistaMessage);
			}
		}
	}
	//mando que se consumio un recurso
	ResourceManager* rm = this->gController->getJuego()->getResourceManager();
	if(rm->hasToNotify()){
		//el primer y ultimo parametro de este mensaje no me importan
		Message* resourceMessege = new Message(rm->getIdAEliminar(),"deleteResource","",0,0,0);
		list<Client*> activeClients= getActiveClients();
		for(list<Client*>::iterator clientIterator=activeClients.begin(); clientIterator!=activeClients.end(); ++clientIterator){
			(*clientIterator)->writeMessagesInQueue(resourceMessege);
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
			Logger::get()->logInfo("Server","verifyClientsConections",ss.str());

			list<int> entitiesToDisconect = gController->getEntitiesOfClient((*clientIterator)->getUserName());
			for(list<int>::iterator it=entitiesToDisconect.begin(); it!=entitiesToDisconect.end();++it){
				Message* messageDisconnect = new Message();
				messageDisconnect->clientDisconect(*it);
				for(list<Client*>::iterator clientIt=activeClients.begin(); clientIt!=activeClients.end(); ++clientIt){
						(*clientIt)->writeMessagesInQueue(messageDisconnect);
				}
			}
		}
	}
}

list<Client*> Server::getActiveClients(){
	list<Client*> activeClients;
	for(map<string,Client*>::iterator clientIterator=this->clients.begin(); clientIterator!=this->clients.end(); ++clientIterator){
		if(clientIterator->second->getStatus()==0){
			activeClients.push_back(clientIterator->second);
		}
	}
	return activeClients;
}

void Server::initConnection(Client *newClient){
	bool validUserName=false;
	stringstream ss;
	while(!validUserName){
		string userName=newClient->readUserName();
			map<string,Client*>::iterator it = this->clients.find(userName);
			if(it != this->clients.end()){
				//El cliente ya existia
				ss << "player " << userName << " already exists...";
				Logger::get()->logInfo("Server","readClientUserName",ss.str());
				
				if(it->second->getStatus()==0){
					//El cliente ya existia y ademas está conectado
					ss.str("");
					ss << userName << " is being used by another player";
					Logger::get()->logInfo("Server","readClientUserName",ss.str());
					newClient->responseUserName("FAIL");
				}else{
					//El cliente ya existia pero estaba desconectado y se vuelve a conectar
					newClient->responseUserName("OK");
					newClient->setUserName(userName);
					validUserName=true;
					ss.str("");
					ss << "player "<< userName << " has reconnected";
					Logger::get()->logInfo("Server","readClientUserName",ss.str());
					//asigno el cliente
					this->clients.at(newClient->getUserName()) = newClient;
					notifyClientReconect(newClient->getUserName());
				}
			}else{
				//El cliente no exitia
				newClient->responseUserName("OK");
				newClient->setUserName(userName);
				validUserName=true;
				ss.str("");
				ss << "player "<< userName << " has joined the game";
				Logger::get()->logInfo("Server","readClientUserName",ss.str());
				//Cada vez que se conecta un cliente agrego un protagonista que tiene un owner
				this->gController->getJuego()->agregarProtagonista(newClient->getUserName());
				this->clients.insert(make_pair(newClient->getUserName(),newClient));
			}
	}
	newClient->startCommunication();

}

void Server::notifyClientReconect(string userName){
	list<Client*> activeClients= getActiveClients();
	list<int> entitiesToDisconect = gController->getEntitiesOfClient(userName);
	for(list<int>::iterator it=entitiesToDisconect.begin(); it!=entitiesToDisconect.end();++it){
		Message* messageReconnect = new Message();
		messageReconnect->clientReconnect(*it);
		for(list<Client*>::iterator clientIt=activeClients.begin(); clientIt!=activeClients.end(); ++clientIt){
			if((*clientIt)->getUserName()!=userName){
			(*clientIt)->writeMessagesInQueue(messageReconnect);
			}
		}
	}
}

//TODO : (FOG)EL SERVER LE MANDA AL CLIENTE LA NUEVA POSICION DE LA ENTIDAD, EL CLIENTE CALCULA LOS NUEVOS TILES, Y SE LOS DEVUELVE AL SERVER
void Server::setSeenTiles() {
	map<string,list<pair<int,int> > > newTilesByClient;
	map<int,EntidadDinamica*> protagonistas =this->gController->getJuego()->getProtagonistas();

	for(map<int,EntidadDinamica*>::iterator it=protagonistas.begin(); it!=protagonistas.end();++it){
		EntidadDinamica * entidad = (*it).second;
		pair<int,int>* position = entidad->getPosition();
		int rangeEntity = entidad->getRangeVisibility();
		string owner = (*it).second->getOwner();
		for (int x = position->first - rangeEntity; x <= position->first + rangeEntity; x++) {
			if ( (x>=0) && (x < gameSettings->getMapWidth())) {
				for (int y = position->second-rangeEntity ; y <= position->second+rangeEntity ; y++) {
					if ((y>=0) && (y < this->gameSettings->getMapHeight())) {
						if((x+y >= position->first + position->second - rangeEntity) && (x+y <= position->first + position->second + rangeEntity)
						&& (x-y >= position->first - position->second - rangeEntity) && (x-y <= position->first - position->second + rangeEntity)) {
							newTilesByClient[owner].push_back(std::make_pair(x,y));
						}
					}
				}
			}
		}
	}

	for( map<string,list<pair<int,int> > >::iterator it = newTilesByClient.begin() ; it!=newTilesByClient.end() ; ++it) {
		Client* client = this->clients[(*it).first];
		if (client->getStatus() == CONECTED) {
			list<pair<int,int> > newTiles = client->setSeenTiles((*it).second);
			for (list<pair<int,int> >::iterator itNewList = newTiles.begin(); itNewList != newTiles.end(); ++itNewList) {
//				stringstream ss;
//				ss << "posX =" << (*itNewList).first << "posY =" << (*itNewList).second;;
//				string str = ss.str();
//				Logger::get()->logInfo("server","seetSeenTiles", str);

				Message* msg = new Message();
				msg->activeTile((*itNewList).first,(*itNewList).second);
				client->writeMessagesInQueue(msg);
			}
		}
	}
}

Server::~Server() {
	for(map<string,Client*>::iterator it=this->clients.begin(); it!=this->clients.end(); ++it){
		it->second->~Client();
	}
	//this->gameSettings = NULL;
	//this->gController = NULL;
	readQueue->~SocketQueue();
	//delete(this->readQueue);
	close(this->serverSocket);
}

