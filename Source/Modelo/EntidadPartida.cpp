/*
 * EntidadPartida.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "EntidadPartida.h"

using namespace std;

EntidadPartida::EntidadPartida() {
	// TODO Auto-generated constructor stub

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

string EntidadPartida::getPathImage(){
	return pathImage;
}

EntidadPartida::~EntidadPartida() {
	// TODO Auto-generated destructor stub
}
