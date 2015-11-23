/*
 * EntidadPartida.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/EntidadPartida.h"

using namespace std;

//TODO es posible que no tenga sentido que todas las entidades tengan target
EntidadPartida::EntidadPartida() {
	this->owner = "";
	this->id = SequenceUtils::GetInstance()->getSequence();
	this->target = 0;
	this->targetPosition = make_pair(0,0);
	this->attacker = "";
	this->builderEffort = 0;
}

int EntidadPartida::getId(){
	return this->id;
}

pair<int,int> EntidadPartida::getTargetPosition(){
	return this->targetPosition;
}

void EntidadPartida::setTargetPosition(pair<int,int> position){
	this->targetPosition = position;
}

int EntidadPartida::getTarget(){
	return this->target;
}

void EntidadPartida::setTarget(int target){
	this->target = target;
}

void EntidadPartida::setPosition(int x,int y){
	this->position.first = x;
	this->position.second = y;
}

//TODO las distancias que devuelve este metodo se tienen que validar en algun lado
list<pair<int,int> > EntidadPartida::getNearestPositions(){
	list<pair<int,int> > nearestPositions;
	//posiciones cercanas a la entidad
	pair<int,int> currentPosition = make_pair(this->position.first + this->width,this->position.second);
	for(; currentPosition.second < this->position.second + this->length ; currentPosition.second++){
		nearestPositions.push_front(currentPosition);
	}

	currentPosition = make_pair(this->position.first,this->position.second + this->length);
	for(; currentPosition.first < this->position.first + this->width ; currentPosition.first++){
		nearestPositions.push_front(currentPosition);
	}

	currentPosition = make_pair(this->position.first,this->position.second-1);
	for(; currentPosition.first < this->position.first + this->width ; currentPosition.first++){
		nearestPositions.push_front(currentPosition);
	}

	currentPosition = make_pair(this->position.first-1,this->position.second);
	for(; currentPosition.second < this->position.second + this->length ; currentPosition.second++){
		nearestPositions.push_front(currentPosition);
	}
	return nearestPositions;
}

pair<int,int> EntidadPartida::getPosition(){
	return this->position;
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

void EntidadPartida::setHealth(int health){
	this->health = health;
}

int EntidadPartida::getHealth(){
	return this->health;
}

void EntidadPartida::setStrength(int strength){
	this->strength = strength;
}

int EntidadPartida::getStrength(){
	return this->strength;
}

void EntidadPartida::setBuilderEffort(int effort){
	this->builderEffort = effort;
}

void EntidadPartida::setPrecision(float precision){
	this->precision = precision;
}

float EntidadPartida::getPrecision(){
	return this->precision;
}

int EntidadPartida::defend(){
	float val = ( rand() % 100 ) / 100;
	if( val <= this->precision )
		return this->strength * val;
	else
		return 0;
}

void EntidadPartida::takeDamage(int damage, string userAttarcker){
	this->notifiable = true;
	int damageTaken = damage - this->defend();
	if( damageTaken <= 0 )
		return;
	int beforeQuantity = this->health;
	this->health = this->health - damageTaken;
	this->attacker = userAttarcker;

	//si la entidad es un recurso lo recolectamos
	if( this->name == "gold" || this->name == "food" || this->name == "wood" || this->name == "rock"  ){
		ResourceCounter::GetInstance()->collectResource(userAttarcker,this->name,beforeQuantity - this->health);
	}
}

void EntidadPartida::takeBuilderEffort(int effort){
	this->health += effort;
}

void EntidadPartida::setOwner(string ownerId){
	this->owner = ownerId;
}

Message* EntidadPartida::getMessage(){
	Message* msg = new Message(this->id, DefaultSettings::getTypeEntity(this->name));
	msg->setName(this->name);
	msg->setPosition(this->position);
	msg->setOwner(this->owner);
	msg->setHealth(this->health);
	msg->setStrength(this->strength);
	msg->setPrecision(this->precision);
	return msg;
}

string EntidadPartida::getOwner(){
	return this->owner;
}

void EntidadPartida::setNotifiable(bool noti){
	this->notifiable = noti;
}

bool EntidadPartida::hasToNotify(){
	return notifiable;
}

string EntidadPartida::getAttacker(){
	return this->attacker;
}

void EntidadPartida::setAttacker(int attackerId){
	 this->attacker = attackerId;
}

bool EntidadPartida::isMaxHealth(){
	return (this->health == this->maxHealth);
}

bool EntidadPartida::isConstructionCompleted(){
		return this->isCompleted;
}
void EntidadPartida::completeConstruction(){
	this->isCompleted = true;
}

EntidadPartida::~EntidadPartida() {
}
