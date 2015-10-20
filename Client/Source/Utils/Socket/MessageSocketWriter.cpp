/*
 * MessageSocketWritter.cpp
 *
 *  Created on: 13 de oct. de 2015
 *      Author: jorlando
 */

#include "../../../Headers/Utils/Socket/MessageSocketWriter.h"

MessageSocketWriter::MessageSocketWriter(int sockfd) {
	this->socket = new SocketUtils(sockfd);
	this->queue = new SocketQueue();
	this->isAlive = true;
}

void MessageSocketWriter::writeMessage(Message *msg){
	this->queue->queuing(msg);
}

int MessageSocketWriter::run(void* data){
	while(this->isAlive){
		while(!this->queue->isEmpty()){
			Message* msg = ((MessageSocketWriter*)data)->queue->pullTail();
			stringstream ss;
			ss << "client is sending message to server." << msg->toString();
			Logger::get()->logDebug("MessageSocketWriter","run",ss.str());
			if(!this->socket->writeMessage(msg)){
			 	Logger::get()->logError("MessageSocketWriter","run","Cant find message to socket");
			 }
		}
	}
	return OK;
}

void MessageSocketWriter::stopWrite(){
	this->isAlive = false;
}

MessageSocketWriter::~MessageSocketWriter() {
	this->socket->~SocketUtils();
	this->queue->~SocketQueue();
}
