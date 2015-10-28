/*
 * MessageSocketReader.cpp
 *
 *  Created on: 13 de oct. de 2015
 *      Author: jorlando
 */

#include "../../../Headers/Utils/Socket/MessageSocketReader.h"

MessageSocketReader::MessageSocketReader(int sockfd,SocketQueue* queueUnique) {
	this->socket = new SocketUtils(sockfd);
	this->queue = queueUnique;
	this->isAlive = true;
}

int MessageSocketReader::run(void *data){
	Logger::get()->logInfo("MessageSocketReader","run","running thread server reader");
	while( this->isAlive ){
		Message* message = this->socket->readMessage();
		this->queue->queuing(message);
	}
	return OK;
}

void MessageSocketReader::shutDown(){
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

Message* MessageSocketReader::readMessageNow(){
	Message *userName = this->socket->readMessage();
	cout << userName->toString();
	return userName;
}

MessageSocketReader::~MessageSocketReader() {
	//esta queue es usada por todos los threads que leen y es la del server, asi que la destruimos por fuera
	this->queue = NULL;
	delete socket;
}
