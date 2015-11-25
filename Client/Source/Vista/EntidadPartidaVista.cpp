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
	this->health = 100;
	this->maxHealth = this->health;
	this->target = NULL;
}

void EntidadPartidaVista::setPosition(int x,int y){
	this->position.first = x;
	this->position.second = y;
}

pair<int,int> EntidadPartidaVista::getPosition(){
	return this->position;
}

EntidadPartidaVista* EntidadPartidaVista::getTarget(){
	return this->target;
}

Direccion EntidadPartidaVista::getStandigDirection(){
	if(this->target){
		pair<int,int> targetPosition = this->target->getPosition();
		//direccion norte
		if( this->position.first == targetPosition.first && this->position.second > targetPosition.second){
			return Norte;
		//direccion noroeste
		}if( this->position.first > targetPosition.first && this->position.second > targetPosition.second){
			return Noroeste;
		//direccion oeste
		}if( this->position.first > targetPosition.first && this->position.second == targetPosition.second){
			return Oeste;
		//direccion suroeste
		}if( this->position.first > targetPosition.first && this->position.second < targetPosition.second){
			return Suroeste;
		//direccion sur
		}if( this->position.first == targetPosition.first && this->position.second < targetPosition.second){
			return Sur;
		//direccion sureste
		}if( this->position.first < targetPosition.first && this->position.second < targetPosition.second){
			return Sureste;
		//direccion este
		}if( this->position.first < targetPosition.first && this->position.second == targetPosition.second){
			return Este;
		//direccion noreste
		}else{
			return Noroeste;
		}
	}else{
		return Noreste;
	}
}

void EntidadPartidaVista::setTarget(EntidadPartidaVista* target){
	this->target = target;
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

void EntidadPartidaVista::drawMe(pair<int,int> isometricPosition, pair<int,int>* offSet, int ciclos){
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

void EntidadPartidaVista::setHealth(int health){
	this->health = health;
	if(this->health> this->maxHealth){
		this->maxHealth = this->health;
	}
}

void EntidadPartidaVista::setStrength(int strength){
	this->strength = strength;
}

void EntidadPartidaVista::setPrecision(float precision){
	this->precision = precision;
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

bool EntidadPartidaVista::isBuildingCompleted(){
	return this->isCompleted;
}

void EntidadPartidaVista::setBuildingCompleted(bool completed){
	this->isCompleted = completed;
}

bool EntidadPartidaVista::isUnderAttack(){
	return (this->health<this->maxHealth);
}

EntidadPartidaVista::~EntidadPartidaVista() {
}
