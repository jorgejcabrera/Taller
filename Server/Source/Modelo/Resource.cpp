/*
 * Resource.cpp
 *
 *  Created on: Oct 17, 2015
 *      Author: juan
 */

#include "../../Headers/Modelo/Resource.h"

using namespace std;

Resource::Resource(string tipo,int x,int y) {
	this->position.first = x;
	this->position.second = y;
	this->width = 1;
	this->length = 1;
	this->name = tipo;
	this->maxHealth = GameSettings::GetInstance()->getConfigAttributeOfEntityAsInt(tipo, "health");
	this->health = this->maxHealth;
	this->beforeQuantity = this->health;
}

void Resource::takeDamage(int damage, string userAttarcker){
	this->notifiable = true;
	this->beforeQuantity = this->health;
	this->health = this->health - damage;
	this->attacker = userAttarcker;
}

int Resource::getAmountCollected(){
	return this->health - this->beforeQuantity;
}

Resource::~Resource() {
}

