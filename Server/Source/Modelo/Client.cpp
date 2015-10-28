/*
 * Client.cpp
 *
 *  Created on: 12 de oct. de 2015
 *      Author: jorlando
 */

#include "../../Headers/Modelo/Client.h"

Client::Client(int identifier, SocketQueue* queueUnique) {
	this->clientId = identifier;
	this->writeThread = new MessageSocketWriter(identifier);
	this->readThread = new MessageSocketReader(this->clientId, queueUnique);
	this->lastReported = time(0);
	this->status = DISCONECTED;
	// TODO settear los primeros lugares vistos en el mapa segun las entities del cliente
}

void Client::reporting(){
	this->lastReported = time(0);
}

void Client::disconect(){
	this->status =DISCONECTED;
}

void Client::connect(){
	this->status =CONECTED;
}

int Client::getStatus(){
	return this->status;
}

int Client::getTimeSinceLastReport(){
	return (time(0)-this->lastReported);
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

//recibe una lista con los tiles vistos
list<pair<int,int> > Client::setSeenTiles( list<pair<int,int> > newTiles) {
	list<pair<int,int> > newSeenTiles;
	if ( this->seenTiles.empty()) {
		for (list<pair<int,int> >::iterator itNewList = newTiles.begin(); itNewList != newTiles.end(); ++itNewList) {
			this->seenTiles.push_back((*itNewList));
			newSeenTiles.push_back((*itNewList));
		}
	} else {
		for (list<pair<int,int> >::iterator itNewList = newTiles.begin(); itNewList != newTiles.end(); ++itNewList) {
			std::list<pair<int,int> >::iterator itSeenTiles = std::find(seenTiles.begin(),seenTiles.end(),*itNewList);
	 		if ( itSeenTiles == this->seenTiles.end()) {
	 			newSeenTiles.push_back((*itNewList));
	 		}
		}
 		for (list<pair<int,int> >::iterator it = newSeenTiles.begin(); it != newSeenTiles.end(); ++it) {
 			seenTiles.push_back((*it));
 		}
	}
	return newSeenTiles;
}

list<pair<int,int> > Client::getSeenTiles() {
	return this->seenTiles;
}

Client::~Client() {
	this->writeThread->shutDown();
	this->readThread->shutDown();
	shutdown(this->clientId, 2);	//2 blocks recv and sending
	close(this->clientId);
	this->writeThread->~MessageSocketWriter();
	this->readThread->~MessageSocketReader();
	delete writeThread;
	delete readThread;

}
