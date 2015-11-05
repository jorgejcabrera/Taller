/*
 * EntidadPartida.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/EntidadPartida.h"

using namespace std;

EntidadPartida::EntidadPartida() {
	this->id = SequenceUtils::GetInstance()->getSequence();
}

int EntidadPartida::getId(){
	return this->id;
}

void EntidadPartida::setPosition(int x,int y){
	this->position.first = x;
	this->position.second = y;
}

pair<int,int>* EntidadPartida::getPosition(){
	return &this->position;
}

int EntidadPartida::getWidth(){
	return this->width;
}

int EntidadPartida::getLength(){
	return this->length;
}

string EntidadPartida::getName(){
	return this->name;
}

void EntidadPartida::setName(string nameImage){
	this->name = nameImage;
}

void EntidadPartida::setVisibilityRange( int range) {
	this->visibilityRange = range;
}

int EntidadPartida::getVisibilityRange() {
	return this->visibilityRange;
}

EntidadPartida::~EntidadPartida() {
}
