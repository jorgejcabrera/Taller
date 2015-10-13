/*
 * Server.cpp
 *
 *  Created on: 4 de oct. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/Server.h"

Server::Server(int port) {
	this->port = port;
	this->serverSocket = 0;
	this->gController = new GameController();
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
/*
int Server::run(void * data){

	while (((Server*) data)->accept_connections){
		socklen_t size = sizeof(struct sockaddr_in);
		int client_socket = accept(((Server*) data)->serverSocket, (struct sockaddr*) &((Server*) data)->remote, &size);
		if (client_socket < 0 ){
			cout << "Error al aceptar cliente"<<endl;
			return -1;
		}else{
			return 0;
		}
	}
	cout << "El servidor dejo de escuchar nuevas conexiones"<<endl;

	return 0;
}*/

void Server::listenClients(){
	//TODO: esto deberia ser un tread corriendo, escuchando si hay nuevas conexiones
	int cliente;
	socklen_t tamano = sizeof(serverAddress);

	if((cliente = accept(this->serverSocket,(struct sockaddr*)&serverAddress,&tamano))>0){
		Client *newClient = new Client(cliente);
		int cantidadDeClients = this->clients.size();
		int clienteActual = cantidadDeClients+1;
		this->clients[clienteActual] = newClient;
		newClient->writeMessagesInQueue(GameSettings::GetInstance()->getListMessageConfiguration());
		newClient->writeMessagesInQueue(this->gController->getTilesMessages());
		//Cada vez que se conecta un cliente agrego un protagonista que tiene un owner
		this->gController->getJuego()->agregarProtagonista(clienteActual);
	}
}

Server::~Server() {
	for(map<int,Client*>::iterator it=this->clients.begin(); it!=this->clients.end(); ++it){
		it->second->~Client();
	}
	close(this->serverSocket);
}
