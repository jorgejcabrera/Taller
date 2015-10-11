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
	this->msg.id = identifier;
	this->msg.tipo = typeEntity;
	this->msg.x = xPosition;
	this->msg.y = yPosition;
}


MessageUpdate::~MessageUpdate(){
}


string MessageUpdate::toString(){
	stringstream ss;
	ss << "id:" << this->msg.id <<";tipo:"<< this->msg.tipo<<";x:" << this->msg.x<<";y:"<<this->msg.y<<";";
	return ss.str();
}

