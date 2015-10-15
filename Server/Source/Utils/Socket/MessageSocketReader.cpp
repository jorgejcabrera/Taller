/*
 * MessageSocketReader.cpp
 *
 *  Created on: 13 de oct. de 2015
 *      Author: jorlando
 */

#include "../../../Headers/Utils/Socket/MessageSocketReader.h"

MessageSocketReader::MessageSocketReader(int sockfd) {
	this->isAlive = true;
	this->socket = new SocketUtils(sockfd);
}

void MessageSocketReader::writeMessage(Message msg){
	this->queue.queuing(msg);
}

int MessageSocketReader::run(void *data){
	while(this->isAlive){
		Message *mensaje = this->socket->readMessage();
		this->writeMessage(*mensaje);
	}
	return OK;
}

MessageSocketReader::~MessageSocketReader() {
}

void MessageSocketReader::stopWrite(){
	this->isAlive = false;
}
