/*
 * MessageUpdate.cpp
 *
 *  Created on: 10 de oct. de 2015
 *      Author: jorlando
 */

#include "../../../Headers/Utils/Socket/MessageUpdate.h"


MessageUpdate::MessageUpdate() {
}

MessageUpdate::MessageUpdate(int identifier, string typeEntity, int xPosition, int yPosition){
	this->msg.set_id(identifier);
	this->msg.set_tipo(typeEntity);
	this->msg.set_x(xPosition);
	this->msg.set_y(yPosition);
}

string MessageUpdate::toString(){
	stringstream ss;
	ss << "id:" << this->msg.id() <<";tipo:"<< this->msg.tipo()<<";x:" << this->msg.x()<<";y:"<<this->msg.y()<<";";
	return ss.str();
}

string MessageUpdate::getSerializeAsString(){
	return this->msg.SerializeAsString();
}

MessageUpdate::~MessageUpdate(){
}


