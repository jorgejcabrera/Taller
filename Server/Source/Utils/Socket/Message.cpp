/*
 * Message.cpp
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#include "../../../Headers/Utils/Socket/Message.h"

Message::Message() {}

//Mensaje usado para novedad de movimiento
Message::Message(int identifier, string nombreEntity, int xPosition, int yPosition){
	this->msg.set_id(identifier);
	this->msg.set_tipo("update");
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
	ss << "id:" << this->msg.id() <<";tipo:"<< this->msg.tipo()<<";x:" << this->msg.x()<<";y:"<<this->msg.y()<<";";
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
