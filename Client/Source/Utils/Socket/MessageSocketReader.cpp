/*
 * MessageReader.cpp
 *
 *  Created on: 11 de oct. de 2015
 *      Author: jorge
 */

#include "../../../Headers/Utils/Socket/MessageSocketReader.h"

MessageSocketReader::MessageSocketReader(int sockfd) {
	this->socket = new SocketUtils(sockfd);
	this->isAlive = true;
}

int MessageSocketReader::run(void *data){
	Logger::get()->logDebug("MessageSocketReader","run","running thread client reader");
	while( this->isAlive ){
		Message* message = this->socket->readMessage();
		this->queue->queuing(*message);
	}
	return OK;
}

list<Message*> MessageSocketReader::getMessagePendingProcess(){
	list<Message*> listaPendientes;
	this->queue->lockQueue();
	while(!this->queue->isEmpty()){
		Message msg = this->queue->pullTailWithoutLock();
		listaPendientes.push_back(&msg);
	}
	this->queue->unlockQueue();
	return listaPendientes;
}

int MessageSocketReader::getCountMessages(){
	return this->queue->getSize();
}

MessageSocketReader::~MessageSocketReader() {
	// TODO Auto-generated destructor stub
}
