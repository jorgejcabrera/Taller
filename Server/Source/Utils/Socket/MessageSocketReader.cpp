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

//Metodo utilizado para leer mensajes on line, la idea es utilizarlo solo para leer el user name
Message* MessageSocketReader::readMessageNow(){
	Message *userName = this->socket->readMessage();
	cout << userName->toString();
	return userName;
}

MessageSocketReader::~MessageSocketReader() {
}
