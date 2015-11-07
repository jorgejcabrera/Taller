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

//Mensaje Utilizado para notificar el nombre de usuario
Message::Message(string nombre){
	this->msg.set_id(0);
	this->msg.set_tipo("username");
	this->msg.set_nombre(nombre);
}

void Message::pingMessage(string nombre){
	this->msg.set_id(0);
	this->msg.set_tipo("ping");
	this->msg.set_nombre(nombre);
}

string Message::toString(){
	stringstream ss;
	ss << " id: " << this->msg.id();
	ss << " tipo: " << this->msg.tipo();
	ss <<  " x: " << this->msg.x();
	ss <<  " y: " << this->msg.y();
	ss <<  " nombre: " << this->msg.nombre();
	ss << " imagen: " << this->msg.imagen();
	ss << " base: " << this->msg.ancho_base();
	ss << " base: " << this->msg.alto_base();
	ss << " fps: " << this->msg.fps();
	ss << " delay: " << this->msg.delay();
	ss << " line: " << this->msg.total_frames_line();
	ss << " dimension: " << this->msg.pixels_dimension();
	ss << " owner: "<< this->msg.owner();
	return ss.str();
}

//Mas cuatro bytes que es lo que ocupa el int del tamaño
//del mensaje que se concaten, al serializar el mensaje
int Message::getSize(){
	return this->msg.ByteSize() + sizeof(int);
}

char* Message::serializeToArray(){
	int size = this->msg.ByteSize();
	char* buffer = new char[ size + sizeof(int) ];
	memset(buffer, 0, size + sizeof(int));

	// convert int to char*
	char integer_string[sizeof(int)];
	memset(integer_string, 0, sizeof(int));
	sprintf(integer_string,"%d",size);

	// coloco el int en el buffer
	memcpy(buffer,integer_string,sizeof(int));

	if( this->msg.SerializePartialToArray(&buffer[sizeof(int)],size)){
		return buffer;
	}else
		return NULL;
}

void Message::setContent(msg_game message){
	this->msg = message;
}

string Message::serializeAsString(){
	return this->msg.SerializeAsString();
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

void Message::setOwner(string userName){
	this->msg.set_owner(userName);
}

string Message::getOwner(){
	return this->msg.owner();
}

void Message::setTarget(int entityId){
	return this->msg.set_target(entityId);
}

int Message::getTarget(){
	return this->msg.target();
}

Message::~Message(){
	this->msg.~msg_game();
}

