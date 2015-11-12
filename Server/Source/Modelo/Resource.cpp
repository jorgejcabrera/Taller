/*
 * Resource.cpp
 *
 *  Created on: Oct 17, 2015
 *      Author: juan
 */

#include "../../Headers/Modelo/Resource.h"

using namespace std;

Resource::Resource(string tipo,int x,int y,int health) {
	this->position.first = x;
	this->position.second = y;
	this->width = 1;
	this->length = 1;
	this->health = health;
	this->name = tipo;
	//Aca estaban los path de los recursos, hay que crear vistaResource en el cliente y ponerlos ahi
}

Resource::~Resource() {
}

