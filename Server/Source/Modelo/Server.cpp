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
				int cantidadDeClients = this->clients.size();
				int clienteActual = cantidadDeClients+1;
				this->clients[clienteActual] = newClient;
				//TODO: esto hay que cambiarlo porque tiene que tener una forma de identificarlo y si se vuelve a conectar un cliente levantar la data
				//Cada vez que se conecta un cliente agrego un protagonista que tiene un owner
				this->gController->getJuego()->agregarProtagonista(clienteActual);

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
		int idUpdate = messageUpdate->getId();
		this->gController->getJuego()->setDestinoProtagonista(idUpdate, messageUpdate->getPositionX(), messageUpdate->getPositionY());
		this->idEntitiesUpdated.push_back(idUpdate);
	}
	this->readQueue->unlockQueue();
}

void Server::notifyClients(){
	map<int,EntidadDinamica*> protagonistas = this->gController->getJuego()->getProtagonistas();
	for(map<int,EntidadDinamica*>::iterator it=protagonistas.begin(); it!=protagonistas.end();++it){
		if (it->second->isWalking()){
			Message *messageUpdate = new Message(it->second->getId(), it->second->getScreenPosition()->first, it->second->getScreenPosition()->second);
			Logger::get()->logDebug("Server","notifyClients",messageUpdate->toString());
			for(map<int,Client*>::iterator clientIterator=this->clients.begin(); clientIterator!=this->clients.end(); ++clientIterator){
				clientIterator->second->writeMessagesInQueue(messageUpdate);
			}
		}
	}
}

Server::~Server() {
	for(map<int,Client*>::iterator it=this->clients.begin(); it!=this->clients.end(); ++it){
		it->second->~Client();
	}
	delete(this->readQueue);
	close(this->serverSocket);
}
