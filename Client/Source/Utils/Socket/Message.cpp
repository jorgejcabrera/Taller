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
	this->serializedMessage(msg.c_str(),msg.length());
}

void Message::serializedMessage(const char * msg, uint32_t size){
	//SET MESSAGE SIZE
	uint32_t be_nro = htonl(size);
	char* ptr_nro = (char*)&be_nro;
	for (unsigned i = 0; i < sizeof(uint32_t); i++){
		this->serialized_message[i] = ptr_nro[i];
	}

	//SET CONTENT
	for (unsigned i = sizeof(uint32_t); i < size + sizeof(uint32_t); i++){
		serialized_message[i] = msg[i - sizeof(uint32_t)];
	}
}

string Message::toString(){
	//TODO: esto no se ejecuta nunca porque defini el metodo como virtual en la clase header
	return this->body;
}

int Message::getLength(){
	return this->length;
}

void Message::setBody(char* bodyReceived){
	this->body.clear();
	this->body.append(bodyReceived);
}

char* Message::getSerializeMessage(){
	return this->serialized_message;
}

char* Message::getBodyToWrite(){
	char* bodyToWrite = new char[this->length];
	for(int idx = 0; idx < this->body.length(); idx++){
		bodyToWrite[idx] = body[idx];
	}
	return bodyToWrite;
}

Message::~Message(){
}

