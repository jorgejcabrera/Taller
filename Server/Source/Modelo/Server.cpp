/*
 * Server.cpp
 *
 *  Created on: 4 de oct. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/Server.h"

Server::Server(int port) {
	try{
		this->sockfd = this->createSocket();
	}catch (int e){
		cout << "No se pudo inicializar el socket" << endl;
	}
	this->accept_connections = true;
	this->port = port;
}
int Server::createSocket(){
	int socketNum = socket(AF_INET, SOCK_STREAM, 0);
	if ( socketNum < 0) {
		throw -1;
	} else {
		return socketNum;
	}
}

int Server::prepareSocket(){
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(port);

	int opt = 1;
	setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

	/**ligamos con el sistema operativo**/
	if ( bind(this->sockfd, (struct sockaddr *)&server, sizeof(struct sockaddr)) < 0 ) {
		cout << "Error al hacer el bind con el sistema operativo" << endl;
		return -1;
	}

	/**escuchamos los clientes**/
	if (listen(this->sockfd, 2) < 0) {
		cout << "Error al escuchar clientes"<<endl;
		return -1;
	}
	return 0;
}

int Server::run(void * data){

	while (((Server*) data)->accept_connections){
		socklen_t size = sizeof(struct sockaddr_in);
		int client_socket = accept(((Server*) data)->sockfd, (struct sockaddr*) &((Server*) data)->remote, &size);
		if (client_socket < 0 ){
			cout << "Error al aceptar cliente"<<endl;
			return -1;
		}else{
			return 0;
		}
	}
	cout << "El servidor dejo de escuchar nuevas conexiones"<<endl;
	return 0;
}

Server::~Server() {
	this->accept_connections = false;
}
