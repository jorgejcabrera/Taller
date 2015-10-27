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
	Logger::get()->logInfo("MessageSocketWriter","run","running thread client writer");
	while(this->isAlive){
		while(!this->queue->isEmpty()){
			Message* msg = ((MessageSocketWriter*)data)->queue->pullTail();
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

void MessageSocketWriter::writeMessageNow(Message* msg){
	this->socket->writeMessage(msg);
	stringstream ss;
	ss << "player "<< msg->getNombre()<<" is connected";
	Logger::get()->logInfo("MessageSocketWriter","writeMessageNow",ss.str());
}

MessageSocketWriter::~MessageSocketWriter() {
	this->socket->~SocketUtils();
	this->queue->~SocketQueue();
}
