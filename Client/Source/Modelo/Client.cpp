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
	this->sockfd = socket(PF_INET, SOCK_STREAM, 0);			//create socket
	this->status = DISCONECTED;								//desconected
}

int Client::connectToServer(){
	int error;
	if ( this->sockfd < 0) {
		cout << "Error initialising socket: "<< gai_strerror(this->sockfd)<< endl;
		//return ERROR;
	}

	//CREATE SOCKET
	struct sockaddr_in s_addr;
	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_family = AF_INET;							//address family internet
	s_addr.sin_port = htons(port);							//set server's port number
	s_addr.sin_addr.s_addr = inet_addr(this->ip.c_str());	//set server's IP

	if ( s_addr.sin_addr.s_addr < 0 ){
		cout << "Error en la direccion IP"<< gai_strerror(s_addr.sin_addr.s_addr)<< endl;
		//return ERROR;
	}
	if ( (error = connect(this->sockfd,(struct sockaddr *)&s_addr, sizeof(s_addr))) < 0){
		cout << "Error connecting to server: "<< gai_strerror(error) << endl;
		this->status = DISCONECTED;
		//return ERROR;
	}else{
		cout << "Conexion con el servidor "<< inet_ntoa(s_addr.sin_addr)<<endl;
		this->status = CONECTED; // conectado :)
	}

	//INITIALIZE THREAD
	this->readThread = new MessageSocketReader(this->sockfd);
	this->writeThread = new MessageSocketWriter(this->sockfd);
	this->readThread->start((MessageSocketReader*) this->readThread );
	this->writeThread->start((MessageSocketWriter*) this->writeThread);

	return OK;
}

void Client::sendMessage(Message msg){
	if (this->status == CONECTED)
		this->writeThread->sendMessage(msg);
}

void Client::readMessage(Message msg){

}

void Client::communicateWithServer(){
	/*Message* mensaje = new Message("");
	this->socketUtils->readMessage(mensaje);
	cout << "CLI Mensaje recibido CLIENT: "<< mensaje->toString() << endl;
	mensaje->setBody("CLI mensaje del CLIENTE AGE OF EMPIRES");
	this->socketUtils->writeQueue->->writeMessage(mensaje);
	this->socketUtils->readMessage(mensaje);
	cout << "CLI Mensaje recibido CLIENT: "<<mensaje->toString()<< endl;*/
}

int Client::getStatus(){
	return this->status;
}

Client::~Client() {
	//this->socketUtils->~SocketUtils();
	shutdown(this->sockfd, 2);	//2 blocks recv and sending
	close(this->sockfd);
}
