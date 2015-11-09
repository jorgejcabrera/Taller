/*
 * EntidadDinamica.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/EntidadDinamica.h"

EntidadDinamica::EntidadDinamica(){
}

EntidadDinamica::EntidadDinamica(string nameEntity,int vel,float x,float y, float widthPixel, float lengthPixels){
	this->caminando = false;
	this->notifiable = false;
	this->position.first = x;
	this->position.second = y;
	this->width = 1;
	this->length = 1;
	this->name = nameEntity;
	this->path = new list<pair<int,int> >();
	this->ciclos = (DefaultSettings::getTileSize() / vel) + 3;
	this->cicloActual = 0;
	this->newPath = false;
	this->target = 0;
}

void EntidadDinamica::nextPosition(){
	this->setNotifiable(false);
	if( !path->empty()){
		if( cicloActual % ciclos == 0){
			pair<int,int> nextTile = path->front();
			path->pop_front();
			this->setNotifiable(true);
			this->newPath = false;
			this->setPosition(nextTile.first,nextTile.second);
		}
		cicloActual++;
	}
}

void EntidadDinamica::setNotifiable(bool noti){
	this->notifiable = noti;
}

bool EntidadDinamica::hasToNotify(){
	return notifiable;
}

list<pair<int,int> >* EntidadDinamica::getPath(){
	return this->path;
}

void EntidadDinamica::setPath(list<pair<int,int> >* caminito){
	this->path->clear();
	this->path = caminito;
}

void EntidadDinamica::setPathIsNew(bool isNew){
	this->newPath = isNew;
}

bool EntidadDinamica::pathIsNew(){
	return this->pathIsNew();
}

bool EntidadDinamica::isWalking(){
	return this->caminando;
}

EntidadDinamica::~EntidadDinamica() {
}
