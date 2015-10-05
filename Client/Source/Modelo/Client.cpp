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
	this->sockfd = socket(AF_INET, SOCK_STREAM, 0);			//create socket
	this->status = -1;										//desconected
}

int Client::connectToServer(){

	if (this->sockfd < 0) {
		cout << "Error initialising socket" << endl;
		return -1;
	}

	//SOCKET
	struct sockaddr_in s_addr;
	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_family = AF_INET;							//address family internet
	s_addr.sin_port = htons(port);							//set server's port number
	s_addr.sin_addr.s_addr = inet_addr(this->ip.c_str());	//set server's IP

	if ( s_addr.sin_addr.s_addr < 0 ){
		cout << "Error en la direccion IP"<< endl;
		return ERROR;
	}
	//set server's in another way :=) --> inet_pton converts addresses to binary.
	/*if ( inet_pton(AF_INET, this->ip.c_str(),&(s_addr.sin_addr)) < 0){
		cout << "Error inet_pton" << endl;
		this->status = -1;
		return -1;
	}*/

	if ( connect(this->sockfd,(struct sockaddr*)&s_addr, sizeof(s_addr)) < 0){
		cout << "Error connecting to server" << endl;
		this->status = -1;
		return ERROR;
	}else {
		this->status = 0; // conectado :)
	}
	return OK;
}

void Client::sendMessage(const char* msg){
}


int Client::getStatus(){
	return this->status;
}

Client::~Client() {
	shutdown(this->sockfd, 2); //2 blocks recv and sending
	close(this->sockfd);
}


