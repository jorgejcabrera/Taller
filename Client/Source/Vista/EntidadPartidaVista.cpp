/*
 * EntidadPartida.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "../../Headers/Vista/EntidadPartidaVista.h"

using namespace std;

EntidadPartidaVista::EntidadPartidaVista() {
	this->id = 0;
	this->seen = false;
	this->salud=100;
}

int EntidadPartidaVista::getSalud(){
	return this->salud;
}

void EntidadPartidaVista::setPosition(int x,int y){
	this->position.first = x;
	this->position.second = y;
}

pair<int,int>* EntidadPartidaVista::getPosition(){
	return &this->position;
}

int EntidadPartidaVista::getWidth(){
	return this->width;
}

int EntidadPartidaVista::getLength(){
	return this->length;
}

string EntidadPartidaVista::getPathImage(){
	return pathImage;
}

void EntidadPartidaVista::setPathImage(string path){
	this->pathImage = path;
}

void EntidadPartidaVista::destruir(){
	this->~EntidadPartidaVista();
}

string EntidadPartidaVista::getSizeString(){
	return this->sizeString;
}

void EntidadPartidaVista::drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos){
}

EntidadPartidaVista::~EntidadPartidaVista() {
}

void EntidadPartidaVista::setId(int identifier){
	this->id = identifier;
}

int EntidadPartidaVista::getId(){
		return this->id;
}

void EntidadPartidaVista::setName(string nameEnt){
	this->name=nameEnt;

}

string EntidadPartidaVista::getName(){
	return this->name;
}

bool EntidadPartidaVista::getSeen() {
	return this->seen;
}

void EntidadPartidaVista::saw() {
	this->seen = true;
}
