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

/*void EntidadPartida::setHealth(int health){
	this->health = health;
}*/

int EntidadPartida::getHealth(){
	return this->health;
}

void EntidadPartida::setStrength(int strength){
	this->strength = strength;
}

int EntidadPartida::getStrength(){
	return this->strength;
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
	this->health = this->health - damageTaken;
	this->attacker = userAttarcker;
}

void EntidadPartida::setOwner(string ownerId){
	this->owner = ownerId;
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

EntidadPartida::~EntidadPartida() {
}
