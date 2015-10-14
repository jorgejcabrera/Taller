/*
 * Client.cpp
 *
 *  Created on: 12 de oct. de 2015
 *      Author: jorlando
 */

#include "../../Headers/Modelo/Client.h"

Client::Client(int identifier) {
	this->clientId = identifier;
	this->writeThread = new MessageSocketWriter(identifier);
	this->writeThread->start((MessageSocketWriter*) this->writeThread);
}

Client::~Client() {
	shutdown(this->clientId, 2);
}

void Client::writeMessagesInQueue(list<Message*> messagesList){
	for(list<Message*>::iterator it=messagesList.begin(); it!=messagesList.end(); ++it){
		//TODO: borrar este cout
		//cout << "Messages: " << (*it)->toString()<<endl;
		this->writeThread->writeMessage((**it));
	}
}

