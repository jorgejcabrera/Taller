/*
 * MessageReader.cpp
 *
 *  Created on: 11 de oct. de 2015
 *      Author: jorge
 */

#include "../../../Headers/Utils/Socket/MessageSocketReader.h"

MessageSocketReader::MessageSocketReader(int sockfd) {
	this->isAlive = true;
	this->socket = new SocketUtils(sockfd);
	this->queue = new SocketQueue();
}

int MessageSocketReader::run(void *data){
	Logger::get()->logInfo("MessageSocketReader","run","running thread client reader");
	while( this->isAlive ){
		Message* message = this->socket->readMessage();
		this->queue->queuing(message);
	}
	return OK;
}

list<Message*> MessageSocketReader::getMessagesToProcess(){
	list<Message*> listaPendientes;
	this->queue->lockQueue();
	while(!this->queue->isEmpty()){
		Message* msg = this->queue->pullTailWithoutLock();
		listaPendientes.push_back(msg);
	}
	this->queue->unlockQueue();
	return listaPendientes;
}

Message* MessageSocketReader::readMessageNow(){
	Message *userName = this->socket->readMessage();
	return userName;
}

void MessageSocketReader::shutDown(){
	this->isAlive = false;
}

MessageSocketReader::~MessageSocketReader() {
	this->queue->~SocketQueue();
	delete socket;
	//delete queue;
}

