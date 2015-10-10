/*
 * Message.cpp
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#include "../../../Headers/Utils/Socket/Message.h"

//TODO: esta clase solo deberia ser Abstracta? ahora tenemos dos tipos de mesanjes.
//No la borro porque sive para hacer pruebas
Message::Message() {}

Message::Message(string msg) {
	this->body = msg;
	this->length = sizeof(char) * msg.length() + sizeof(uint32_t);
}

string Message::toString(){
	return this->body;
}

int Message::getBodySize(){
	return this->length;
}

void Message::setBody(char* bodyReceived){
	this->body.clear();
	this->body.append(bodyReceived);
}
Message::~Message(){
}

char * Message::getBodyToWrite(){
	char* bodyToWrite = new char[this->length];
	for(int idx = 0; idx < this->body.length(); idx++){
		bodyToWrite[idx] = body[idx];
	}
	return bodyToWrite;
}
