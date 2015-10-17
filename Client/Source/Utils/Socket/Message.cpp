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

//Mas cuatro bytes que es lo que ocupa el int del tamaño
//del mensaje que se concaten, al serializar el mensaje
int Message::getSize(){
	return this->msg.ByteSize() + 4;
}

char* Message::serializeToArray(){
	int size = this->msg.ByteSize();
	char* buffer = new char[size+4];
	memset(&buffer, 0,size+4);
	buffer[0]=size;
	if( this->msg.SerializePartialToArray(&buffer[1],size) )
		return buffer;
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

string Message::getTipo(){
	return this->msg.tipo();
}

int Message::getId(){
	return this->msg.id();
}

int Message::getPositionX(){
	return this->msg.x();
}

int Message::getPositionY(){
	return this->msg.y();
}

string Message::getNombre(){
	return this->msg.nombre();
}

string Message::getImagen(){
	return this->msg.imagen();
}

int Message::getAnchoBase(){
	return this->msg.ancho_base();
}

int Message::getAltoBase(){
	return this->msg.alto_base();
}

int Message::getFps(){
	return this->msg.fps();
}

int Message::getDelay(){
	return this->msg.delay();
}

int Message::getTotalFramesLine(){
	return this->msg.total_frames_line();
}

int Message::getPixelsDimension(){
	return this->msg.pixels_dimension();
}

