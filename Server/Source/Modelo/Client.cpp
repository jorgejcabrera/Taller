/*
 * Client.cpp
 *
 *  Created on: 12 de oct. de 2015
 *      Author: jorlando
 */

#include "../../Headers/Modelo/Client.h"

Client::Client(int identifier, SocketQueue *queueUnique) {
	this->clientId = identifier;
	this->writeThread = new MessageSocketWriter(identifier);
	this->readThread = new MessageSocketReader(this->clientId, queueUnique);
	this->lastReported = time(0);
}

Client::~Client() {
	shutdown(this->clientId, 2);
}

void Client::reporting(){
	this->lastReported = time(0);
}

bool Client::isActive(){
	//Si no recibo novedades por 15 segundos lo marco como inactivo;
	return((time(0)-this->lastReported)<DefaultSettings::getTimeOut());
}

void Client::writeMessagesInQueue(list<Message*> messagesList){
	for(list<Message*>::iterator it=messagesList.begin(); it!=messagesList.end(); ++it){
		this->writeThread->writeMessage((*it));
	}
}

void Client::writeMessagesInQueue(Message* message){
		this->writeThread->writeMessage(message);
}

//Lanza los threads de lectura y escritura
void Client::startCommunication(){
	this->writeThread->start((MessageSocketWriter*) this->writeThread);
	this->readThread->start((MessageSocketReader*) this->readThread);
}

string Client::readUserName(){
	Message *userNameMessage = this->readThread->readMessageNow();
	return userNameMessage->getNombre();
}

void Client::responseUserName(string isOk){
	this->writeThread->writeMessageNow(new Message(isOk));
}

string Client::getUserName(){
	return this->userName;
}

void Client::setUserName(string myName){
	this->userName = myName;
}
