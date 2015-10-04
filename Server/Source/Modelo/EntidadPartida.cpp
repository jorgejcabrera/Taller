/*
 * EntidadPartida.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/EntidadPartida.h"

using namespace std;

EntidadPartida::EntidadPartida() {
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

void EntidadPartida::setPathImage(string path){
	this->pathImage = path;
}

void EntidadPartida::destruir(){
	this->~EntidadPartida();
}

string EntidadPartida::getSizeString(){
	return this->sizeString;
}

void EntidadPartida::drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos){
}

EntidadPartida::~EntidadPartida() {
}