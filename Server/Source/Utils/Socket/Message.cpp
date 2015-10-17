/*
 * Message.cpp
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#include "../../../Headers/Utils/Socket/Message.h"

Message::Message() {}

//Mensaje usado para novedad de movimiento
Message::Message(int identifier, int xPosition, int yPosition){
	this->msg.set_id(identifier);
	this->msg.set_tipo("update");
	this->msg.set_x(xPosition);
	this->msg.set_y(yPosition);
}

//Mesaje utilizado para mandar por primera vez una entidad
Message::Message(int identifier,string tipoMessage, string nombreEntity, int xPosition, int yPosition){
	this->msg.set_id(identifier);
	this->msg.set_tipo(tipoMessage);
	this->msg.set_nombre(nombreEntity);
	this->msg.set_x(xPosition);
	this->msg.set_y(yPosition);
}

//Mensaje usado para configuracion
Message::Message(string nameEntity, string thePath, int anchoBase, int altoBase, int fps, int delay, int totalFramesLine, int pixelDimension){
	this->msg.set_id(0);
	this->msg.set_tipo("config");
	this->msg.set_nombre(nameEntity);
	this->msg.set_imagen(thePath);
	this->msg.set_ancho_base(anchoBase);
	this->msg.set_alto_base(altoBase);
	this->msg.set_fps(fps);
	this->msg.set_delay(delay);
	this->msg.set_total_frames_line(totalFramesLine);
	this->msg.set_pixels_dimension(pixelDimension);
}

//Mensaje utilizado para mandar tiles o dimension de la ventana
Message::Message(string tipo, string nombreEntity, int xPosition, int yPosition){
	this->msg.set_id(0);
	this->msg.set_tipo(tipo);
	this->msg.set_nombre(nombreEntity);
	this->msg.set_x(xPosition);
	this->msg.set_y(yPosition);
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
	return ss.str();
}

//Mas cuatro bytes que es lo que ocupa el int del tamaño
//del mensaje que se concaten, al serializar el mensaje
int Message::getSize(){
	return this->msg.ByteSize()+4;
}

char* Message::serializeToArray(){
	int size = this->msg.ByteSize();
	char* buffer = new char[size+sizeof(int)];
	memset(&buffer, 0,size+sizeof(int));
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

int Message::getId(){
	return this->msg.id();
}

int Message::getPositionX(){
	return this->msg.x();
}

int Message::getPositionY(){
	return this->msg.y();
}
