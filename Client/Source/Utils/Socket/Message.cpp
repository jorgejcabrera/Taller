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

/*Message::Message(string msg) {
	this->body = msg;
	//TODO verificar al momento de leetura del lado del servidor si es necesario que lea un poco demas
	this->length = sizeof(char) * msg.length() + sizeof(uint32_t);
	this->serialized_message = new char[length];
	this->serializedMessage();
}*/

//TODO es posible que esto no lo tengos que usar mas
/*void Message::serializedMessage(){
	//clear memory
	memset(serialized_message, NULL, length);

	//set message size
	uint32_t be_nro = htonl(this->body.size());
	char* ptr_nro = (char*)&be_nro;
	for (unsigned i = 0; i < sizeof(uint32_t); i++){
		this->serialized_message[i] = ptr_nro[i];
		cout << this->serialized_message[i]<<endl;
	}

	//set content
	const char* msg = this->body.c_str();
	for (unsigned i = sizeof(uint32_t); i < this->body.size() + sizeof(uint32_t); i++){
		this->serialized_message[i] = this->body.c_str()[i - sizeof(uint32_t)];
		cout << this->serialized_message[i]<<endl;
	}
}*/

string Message::toString(){
	//TODO: esto no se ejecuta nunca porque defini el metodo como virtual en la clase header
	return NULL;
}

int Message::getLength(){
	//return this->length;
	return 0;
}

void Message::setBody(char* bodyReceived){
/*	this->body.clear();
	this->body.append(bodyReceived);*/
}

char* Message::getSerializeMessage(){
	//return this->serialized_message;
	return NULL;
}

/*char* Message::getBodyToWrite(){
	char* bodyToWrite = new char[this->length];
	for(int idx = 0; idx < this->body.length(); idx++){
		bodyToWrite[idx] = body[idx];
	}
	return bodyToWrite;
}*/

Message::~Message(){
}

