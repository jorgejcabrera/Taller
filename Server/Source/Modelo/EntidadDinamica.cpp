/*
 * EntidadDinamica.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/EntidadDinamica.h"

EntidadDinamica::EntidadDinamica(){
}

EntidadDinamica::EntidadDinamica(string nameEntity,int vel,float x,float y,float widthPixel,float lengthPixels){
	this->walking = false;
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
	this->readyToInteract = false;
	this->health = health;
	this->maxHealth = GameSettings::GetInstance()->getConfigAttributeOfEntityAsInt(nameEntity, "health");
	this->health = this->maxHealth;
	this->isCompleted = true;
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

int EntidadDinamica::getDamage(){
	float val = ( rand() % 100 ) / 100;
	if( val <= this->precision ){
		return this->strength;
	}else{
		return 0;
	}
}

void EntidadDinamica::attackTo(EntidadPartida* entity){
	stringstream ss;
	ss << "estamos atacando. La salud de la entidad era de " << entity->getHealth();
	Logger::get()->logDebug("EntidadDinamica","attackTo",ss.str()); 
	entity->takeDamage(this->getDamage(), this->getOwner());
	ss.str("");
	ss << "La salud de la entidad es " << entity->getHealth();
	Logger::get()->logDebug("EntidadDinamica","attackTo",ss.str()); 
}

void EntidadDinamica::construct(EntidadPartida* entity){
	entity->takeBuilderEffort(this->builderEffort);
}

bool EntidadDinamica::isReadyToInteract(){
	return this->readyToInteract;
}

void EntidadDinamica::prepareToInteract(bool value){
	this->readyToInteract = value;
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

Message* EntidadDinamica::getEntityMessage(){
	Message* msg = new Message(this->id, DefaultSettings::getTypeEntity(this->name));
	msg->setName(this->name);
	msg->setPosition(this->position);
	msg->setOwner(this->owner);
	msg->setHealth(this->health);
	msg->setStrength(this->strength);
	msg->setPrecision(this->precision);
	return msg;
}

bool EntidadDinamica::pathIsNew(){
	return this->pathIsNew();
}

bool EntidadDinamica::isWalking(){
	return this->walking;
}

EntidadDinamica::~EntidadDinamica() {
}
