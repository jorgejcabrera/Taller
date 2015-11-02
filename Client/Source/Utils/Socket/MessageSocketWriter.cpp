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

void MessageSocketWriter::writeMessage(Message* msg){
	this->queue->queuing(msg);
}

int MessageSocketWriter::run(void* data){
	Logger::get()->logInfo("MessageSocketWriter","run","running thread client writer");
	while( this->isAlive ){
		while(!this->queue->isEmpty()){
			Message* msg = ((MessageSocketWriter*)data)->queue->pullTail();
			if( msg == NULL){
				Logger::get()->logError("MessageSocketWriter","run","There was a problem. The message format is invalid or null");
				return ERROR;
			}
			this->socket->writeMessage(msg);
		}
	}
	return OK;
}

void MessageSocketWriter::clearQueue(){
	Logger::get()->logInfo("MessageSocketWriter","clearQueue","Client disconnected, so all pending messages are clear");
	this->queue->clear();
}

int MessageSocketWriter::countMessage(){
	return this->queue->getSize();
}

void MessageSocketWriter::shutDown(){
	this->isAlive = false;
}

void MessageSocketWriter::writeMessageNow(Message* msg){
	this->socket->writeMessage(msg);
	stringstream ss;
	ss << "player "<< msg->getNombre()<<" is connected";
	Logger::get()->logInfo("MessageSocketWriter","writeMessageNow",ss.str());
}

MessageSocketWriter::~MessageSocketWriter() {
	this->queue->~SocketQueue();
	delete socket;
	//delete queue;
}
