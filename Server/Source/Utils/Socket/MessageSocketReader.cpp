/*
 * MessageSocketReader.cpp
 *
 *  Created on: 13 de oct. de 2015
 *      Author: jorlando
 */

#include "../../../Headers/Utils/Socket/MessageSocketReader.h"

MessageSocketReader::MessageSocketReader(int sockfd,SocketQueue *queueUnique) {
	this->isAlive = true;
	this->socket = new SocketUtils(sockfd);
	this->queue = queueUnique;
}

int MessageSocketReader::run(void *data){
	Logger::get()->logDebug("MessageSocketReader","run","running thread server reader");
	while( this->isAlive ){
		Message *message = this->socket->readMessage();
		this->queue->queuing(message);
	}
	return OK;
}

MessageSocketReader::~MessageSocketReader() {
}

void MessageSocketReader::stopWrite(){
	this->isAlive = false;
}

list<Message*> MessageSocketReader::getMessagePendingProcess(){
	list<Message*> listaPendientes;
	/*this->queue->lockQueue();
	while(!this->queue->isEmpty()){
		Message *msg = this->queue->pullTailWithoutLock();
		listaPendientes.push_back(msg);
	}
	this->queue->unlockQueue();
	*/
	return listaPendientes;
}
