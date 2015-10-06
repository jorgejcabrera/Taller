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
	this->sockfd = 0;
	this->status = -1;										//desconected
}

int Client::connectToServer(){
	int error;
	this->sockfd = socket(PF_INET, SOCK_STREAM, 0);			//create socket
	if ( this->sockfd < 0) {
		cout << "Error initialising socket: "<< gai_strerror(this->sockfd)<< endl;
		return -1;
	}

	//SOCKET
	struct sockaddr_in s_addr;
	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_family = AF_INET;							//address family internet
	s_addr.sin_port = htons(port);							//set server's port number
	s_addr.sin_addr.s_addr = inet_addr(this->ip.c_str());	//set server's IP

	if ( s_addr.sin_addr.s_addr < 0 ){
		cout << "Error en la direccion IP"<< gai_strerror(s_addr.sin_addr.s_addr)<< endl;
		return ERROR;
	}
	//set server's in another way :=) --> inet_pton converts addresses to binary.
	/*if ( inet_pton(AF_INET, this->ip.c_str(),&(s_addr.sin_addr)) < 0){
		cout << "Error inet_pton" << endl;
		this->status = -1;
		return -1;
	}*/
	if ( (error = connect(this->sockfd,(struct sockaddr *)&s_addr, sizeof(s_addr))) < 0){
		cout << "Error connecting to server: "<< gai_strerror(error) << endl;
		this->status = -1;
		return ERROR;
	}else {
		cout << "Conexion con el servidor "<<inet_ntoa(s_addr.sin_addr)<<endl;
		this->status = 0; // conectado :)
	}
	return OK;
}

bool Client::sendMessage(char* buffer,const char* msg){
	strcpy(buffer,msg);
	ssize_t n = write(this->sockfd,buffer,1024);				//bufsize hoy en dia esta hardcodeado a 1024
	if(n < 0)
		cout<<"ERROR writing to socket: "<< gai_strerror(n)<<endl;
	return (n<0);

}

void Client::communicateWithServer(){
	Socket *socketClient = new Socket(this->sockfd);
	Message *mensaje = new Message("");
	socketClient->readMessage(mensaje);
	cout << "CLI Mensaje recibido CLIENT: "<<mensaje->getBody()<< endl;
	mensaje->setBody("CLI mensaje del CLIENTE AGE OF EMPIRES");
	socketClient->writeMessage(mensaje);
	socketClient->readMessage(mensaje);
	cout << "CLI Mensaje recibido CLIENT: "<<mensaje->getBody()<< endl;
	socketClient->~Socket();
	/*
	 * readFull(cliente,buffer,bufsize);
	  writeFull(cliente,buffer,bufsize,"CLI mensaje del CLIENTE AGE OF EMPIRES");
	  readFull(cliente,buffer,bufsize);
	  cout<<"CLI Conexion terminada. Programa finalizado\n\n";
	  */
}


int Client::getStatus(){
	return this->status;
}

Client::~Client() {
	shutdown(this->sockfd, 2); //2 blocks recv and sending
	close(this->sockfd);
}


