/*
 * MessageSocketWritter.cpp
 *
 *  Created on: 13 de oct. de 2015
 *      Author: jorlando
 */

#include "../../../Headers/Utils/Socket/MessageSocketWriter.h"

MessageSocketWriter::MessageSocketWriter(int sockfd) {
	this->socket = new SocketUtils(sockfd);
	this->isAlive = true;
}

void MessageSocketWriter::writeMessage(Message *msg){
	//Logger::get()->logDebug("MessageSocketWriter","writeMessage",msg->toString());
	this->queue.queuing(msg);
}

int MessageSocketWriter::run(void* data){
	Logger::get()->logDebug("MessageSocketWriter","run","thread socket writter is running");
	while(this->isAlive){
		while(!this->queue.isEmpty()){
			Message* msg = ((MessageSocketWriter*)data)->queue.pullTail();
			if(!this->socket->writeMessage(msg)){
			 	Logger::get()->logError("MessageSocketWriter","run","Cant find message to socket");
			 }
		}
	}
	return OK;
}

MessageSocketWriter::~MessageSocketWriter() {
}

void MessageSocketWriter::stopWrite(){
	this->isAlive = false;
}

//Este metodo se usa para notificar el nombre de usuario que tiene que ser en el momento, no puede seguir el ciclo normal
void MessageSocketWriter::writeMessageNow(Message *msg){
	this->socket->writeMessage(msg);
	Logger::get()->logDebug("MessageSocketWriter","writeMessageNow",msg->toString());
}
