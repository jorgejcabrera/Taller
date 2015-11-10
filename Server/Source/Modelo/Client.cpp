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
}

void Client::reporting(){
	this->lastReported = time(0);
}

/*void Client::disconect(){
	this->status = DISCONECTED;
	this->writeThread->shutDown();
	this->readThread->shutDown();
	shutdown(this->clientId, 2);	//2 blocks recv and sending
	close(this->clientId);

	this->writeThread->shutDown();
	this->writeThread->join(NULL);

	this->readThread->shutDown();
	this->readThread->join(NULL);
}*/

void Client::connect(){
	this->status = CONECTED;
	this->writeThread->restart();
	this->readThread->restart();
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
	Message* userNameMessage = this->readThread->readMessageNow();
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
	 			seenTiles.push_back((*itNewList));
	 		}
		}
	}
	return newSeenTiles;
}

list<pair<int,int> > Client::getSeenTiles() {
	return this->seenTiles;
}

list<Message*> Client::getSeenTilesAsMessages(){
	list<Message*> tilesVistos;
	for(list<pair<int,int> >::iterator tilesIte=seenTiles.begin(); tilesIte!=seenTiles.end();++tilesIte){
		Message* msg = new Message();
		msg->activeTile((*tilesIte).first,(*tilesIte).second);
		tilesVistos.push_back(msg);
	}
	return tilesVistos;
}

Message* Client::getInitialOffsetAsMessage(){
	Message* msg = new Message();
	msg->initialOffset(this->initialOffset.first, this->initialOffset.second);
	return msg;
}


void Client::disconect(){
	this->status = DISCONECTED;
	this->writeThread->shutDown();
	this->readThread->shutDown();
	shutdown(this->clientId, 2);	//2 blocks recv and sending
	close(this->clientId);

	this->writeThread->shutDown();
	this->writeThread->join(NULL);

	this->readThread->shutDown();
	this->readThread->join(NULL);
}

void Client::setInitialOffset(int x, int y){
	this->initialOffset.first=x;
	this->initialOffset.second=y;
}

pair<int,int> Client::getInitialOffset(){
	return this->initialOffset;
}

Client::~Client() {
	shutdown(this->clientId, 2);	//2 blocks recv and sending
	close(this->clientId);

	this->writeThread->shutDown();
	this->writeThread->join(NULL);

	this->readThread->shutDown();
	this->readThread->join(NULL);

	this->writeThread->~MessageSocketWriter();
	this->readThread->~MessageSocketReader();

	delete writeThread;
	delete readThread;
}
