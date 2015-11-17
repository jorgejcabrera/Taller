/*
 * ResourceCounter.cpp
 *
 *  Created on: Oct 28, 2015
 *      Author: juan
 */

#include "../../Headers/Modelo/ResourceCounter.h"

ResourceCounter::ResourceCounter() {
	int cantInicial = 10;
	this->alimento = cantInicial;
	this->oro = cantInicial;
	this->madera = cantInicial;
	this->roca = cantInicial;
}

void ResourceCounter::gastar(string recurso) {
	if(recurso == "gold")
		this->oro--;
	if(recurso == "wood")
		this->madera--;
	if(recurso == "chori")
		this->alimento--;
	if(recurso == "rock")
		this->roca--;
}

void ResourceCounter::increase(string recurso,int quantity){
	if(recurso == "gold")
		this->oro += quantity;
	if(recurso == "wood")
		this->madera += quantity;
	if(recurso == "chori")
		this->alimento += quantity;
	if(recurso == "rock")
		this->roca += quantity;
}

int ResourceCounter::getGold(){
	return this->oro;
}

int ResourceCounter::getFood(){
	return this->alimento;
}

int ResourceCounter::getWood(){
	return this->madera;
}

int ResourceCounter::getRock(){
	return this->roca;
}

ResourceCounter::~ResourceCounter() {
	// TODO Auto-generated destructor stub
}

