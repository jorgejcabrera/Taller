/*
 * EntidadPartida.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "../../Headers/Vista/EntidadPartidaVista.h"

EntidadPartidaVista::EntidadPartidaVista() {
	this->id = 0;
	this->seen = false;
	//TODO sacar esto, lo dejo asi sino a veces lo pone como el valor maximo de int
	this->health = 100;
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

string EntidadPartidaVista::getSizeString(){
	return this->sizeString;
}

void EntidadPartidaVista::drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos){
}

void EntidadPartidaVista::setId(int identifier){
	this->id = identifier;
}

int EntidadPartidaVista::getId(){
	return this->id;
}

int EntidadPartidaVista::getHealth(){
	return this->health;
}

int EntidadPartidaVista::getStrength(){
	return this->strength;
}

float EntidadPartidaVista::getPrecision(){
	return this->precision;
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

void EntidadPartidaVista::setOwner(string newOwner){
	this->owner = newOwner;
}
string EntidadPartidaVista::getOwner(){
	return this->owner;
}

EntidadPartidaVista::~EntidadPartidaVista() {
}
