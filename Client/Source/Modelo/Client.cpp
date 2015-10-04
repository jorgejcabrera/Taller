/*
 * Client.cpp
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/Client.h"

Client::Client(string ip, int port) {
	this->ip = ip;
	this->port = port;
	this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	this->status = -1;			//desconectado
}

int Client::connectToServer(){

	if (this->sockfd < 0) {
		cout << "Error al crear socket" << endl;
		return -1;
	}

	struct sockaddr_in s_addr;
	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(port);

	//inet_pton converts addresses to binary.
	if (inet_pton(AF_INET, this->ip.c_str(), &(s_addr.sin_addr)) < 0){
		cout << "Error inet_pton" << endl;
		this->status = -1;
		return -1;
	}

	if (connect(this->sockfd, (struct sockaddr*) & s_addr, sizeof(struct sockaddr)) < 0){
		cout << "Error no podemos conectar al socket" << endl;
		this->status = -1;
		return -1;
	}else {
		this->status = 0; // conectado :)
	}
	return 0;
}

void Client::sendMessage(string msg){
	//TODO: ver la logica para enviar mensajes
}


int Client::getStatus(){
	return this->status;
}

Client::~Client() {
	shutdown(this->sockfd, 2); //2 blocks recv and sending
	close(this->sockfd);
}


