/*
 * Message.cpp
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#include "../../../Headers/Utils/Socket/Message.h"

Message::Message(string msg) {
	this->body = msg;
}

string Message::getBody(){
	return this->body;
}

int Message::getBodySize(){
	return this->sizeBody;
}

void Message::setBody(char* bodyReceived){
	this->body.clear();
	this->body.append(bodyReceived);
}
/*
void Message::setBody(string bodyReceived){
	this->body.clear();
	this->body.append(bodyReceived);
}
*/
Message::~Message(){
}

char * Message::getBodyToWrite(){
	char* bodyToWrite = new char[this->sizeBody];
	for(int idx = 0; idx < this->body.length(); idx++){
		bodyToWrite[idx] = body[idx];
	}
	return bodyToWrite;
}
