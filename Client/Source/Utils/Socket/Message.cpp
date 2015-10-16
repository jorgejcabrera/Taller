/*
 * Message.cpp
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#include "../../../Headers/Utils/Socket/Message.h"

Message::Message() {}
	
Message::Message(int identifier, string typeEntity, int xPosition, int yPosition){
	this->msg.set_id(identifier);
	this->msg.set_tipo(typeEntity);
	this->msg.set_x(xPosition);
	this->msg.set_y(yPosition);
}

string Message::toString(){
	stringstream ss;
	ss << " id: " << this->msg.id() << " tipo: " << this->msg.tipo() << " nombre: " << this->msg.nombre() << " imagen: " << this->msg.imagen() << " base: " << this->msg.ancho_base() << " base: " << this->msg.alto_base() << " fps: " << this->msg.fps() << " delay: " << this->msg.delay() << " line: " << this->msg.total_frames_line() << " dimension: " << this->msg.pixels_dimension();
	return ss.str();
}

int Message::getSize(){
	return this->msg.ByteSize();
}

char* Message::serializeToArray(){
	int size = this->msg.ByteSize();
	char* array = new char[size];
	if( this->msg.SerializePartialToArray(array,size) )
		return array;
	else
		return NULL;
}

void Message::setContent(msg_game message){
	this->msg = message;
}

string Message::serializeAsString(){
	return this->msg.SerializeAsString();
}

Message::~Message(){
}

