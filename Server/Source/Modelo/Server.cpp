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
	//this->accept_1onnections = true;

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
	int client;
	socklen_t tamano = sizeof(serverAddress);
	while((client = accept(this->serverSocket,(struct sockaddr*)&serverAddress,&tamano))>0){ //aceptamos la conexion retorna negativo si falla
		SocketUtils *socketClient = new SocketUtils(client);
		Message *mensaje = new Message("SRV Servidor Conectado");
		socketClient->writeMessage(mensaje);
	    cout<<"SRV Conexion con el cliente EXITOSA"<<endl;
	    socketClient->readMessage(mensaje);
	    cout << "SRV Mensaje recibido SERVER: "<<mensaje->toString()<< endl;
	    mensaje->setBody("SRV mensaje del SERVER");
	    socketClient->writeMessage(mensaje);
	    cout << "SRV El servidor termino la conexion"<<endl;
		socketClient->~SocketUtils();
	    close(client);
	    cout << "SRV Conecte nuevo cliente."<<endl;
	  }
}

Server::~Server() {
	//this->accept_connections = false;
	close(this->serverSocket);
}
