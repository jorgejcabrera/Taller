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
	this->queue = new SocketQueue();
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
				Client *newClient = new Client(cliente, this->queue);
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
				//newClient->writeMessagesInQueue(this->gController->getTilesMessages());

				//Mando las entidades que tiene el mapa
				//newClient->writeMessagesInQueue(gController->getEntitiesMessages());

				//Mando los protagonistas hasta el momento
				//newClient->writeMessagesInQueue(gController->getProtagonistasMessages());
			}
	}
	cout << "FIN RUN" <<endl;
	return 0;
}

void Server::processReceivedMessages(){
	this->queue->lockQueue();
	/* 1- Bajo todos los mansajes de la cola
	 * 2- actualizo la posicion de los protagonistas
	 * 3- armo una lista de los protagonistas que actualice para solo notificar esos  los clientes*/
	this->idEntitiesUpdated.clear();
	while(!this->queue->isEmpty()){
		Message messageUpdate = this->queue->pullTailWithoutLock();
		int idUpdate = messageUpdate.getId();
		this->gController->getJuego()->setDestinoProtagonista(idUpdate, messageUpdate.getPositionX(), messageUpdate.getPositionY());
		this->idEntitiesUpdated.push_back(idUpdate);
	}
	this->queue->unlockQueue();
}

void Server::notifyClients(){
	for(list<int>::iterator idProtagonistaIterate=this->idEntitiesUpdated.begin(); idProtagonistaIterate!=this->idEntitiesUpdated.end(); ++idProtagonistaIterate){
		for(map<int,Client*>::iterator it=this->clients.begin(); it!=this->clients.end(); ++it){
			pair<float,float>* position = this->gController->getJuego()->getPositionOfProtagonistaById(*idProtagonistaIterate);
			Message *messageUpdate = new Message(*idProtagonistaIterate, position->first, position->second);
			//TODO revisar que se mande bien el mensaje
			//cout << "Novedad: "<< messageUpdate->toString() <<endl;
			it->second->writeMessagesInQueue(messageUpdate);
		}
	}
	this->idEntitiesUpdated.clear();
}

Server::~Server() {
	for(map<int,Client*>::iterator it=this->clients.begin(); it!=this->clients.end(); ++it){
		it->second->~Client();
	}
	delete(this->queue);
	close(this->serverSocket);
}
