/*
 * Client.cpp
 *
 *  Created on: 12 de oct. de 2015
 *      Author: jorlando
 */

#include "../../Headers/Modelo/Client.h"

Client::Client(int identifier) {
	this->clientId = identifier;
}

Client::~Client() {
	//close(this->clientId);
}

void Client::writeMessagesInQueue(list<Message*> messagesList){
	for(list<Message*>::iterator it=messagesList.begin(); it!=messagesList.end(); ++it){
		//TODO: borrar este cout
		//cout << "Messages: " << (*it)->toString()<<endl;
		this->queue.queuing(*it);
	}
}

