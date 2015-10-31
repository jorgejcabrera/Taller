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
	//will go away on its own upon completion.
	SDL_DetachThread(this->getThread());
	Logger::get()->logInfo("MessageSocketWriter","run","writer thread is running");
	while(this->isAlive){
		stringstream ss;
		while(!this->queue->isEmpty()){
			Message* msg = ((MessageSocketWriter*)data)->queue->pullTail();
			if(!this->socket->writeMessage(msg)){
			 	Logger::get()->logError("MessageSocketWriter","run","Cant find message to socket");
			 }
		}
		//SDL_Delay(100);
	}
	return OK;
}

void MessageSocketWriter::shutDown(){
	this->isAlive = false;
}

void MessageSocketWriter::writeMessageNow(Message *msg){
	this->socket->writeMessage(msg);
}

MessageSocketWriter::~MessageSocketWriter() {
	this->queue->~SocketQueue();
	delete socket;
}