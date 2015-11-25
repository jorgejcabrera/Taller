/*
 * ResourceCounter.cpp
 *
 *  Created on: Oct 28, 2015
 *      Author: juan
 */

#include "../../Headers/Modelo/ResourceCounter.h"

ResourceCounter::ResourceCounter() {
	this->food = INIT_CANT;
	this->gold = INIT_CANT;
	this->wood = INIT_CANT;
	this->rock = INIT_CANT;
}

void ResourceCounter::gastar(string recurso) {
	if(recurso == "gold")
		this->gold--;
	if(recurso == "wood")
		this->wood--;
	if(recurso == "food")
		this->food--;
	if(recurso == "rock")
		this->rock--;
}

void ResourceCounter::refund(string type){
	map<string,int> costs = DefaultSettings::getCostsOf(type);
	for (map<string,int>::iterator it = costs.begin(); it != costs.end(); ++it){
		if( it->first == "gold" ){
			this->gold += it->second;
		}else if( it->first == "food" ){
			this->food += it->second;
		}else if(it->first == "wood" ){
			this->wood += it->second;
		}else{
			this->rock += it->second;
		}
	}
}

void ResourceCounter::increase(string recurso,int quantity){
	if(recurso == "gold")
		this->gold = quantity + INIT_CANT;
	if(recurso == "wood")
		this->wood = quantity + INIT_CANT;
	if(recurso == "food")
		this->food = quantity + INIT_CANT;
	if(recurso == "rock")
		this->rock = quantity + INIT_CANT;
}

int ResourceCounter::getGold(){
	return this->gold;
}

int ResourceCounter::getFood(){
	return this->food;
}

int ResourceCounter::getWood(){
	return this->wood;
}

int ResourceCounter::getRock(){
	return this->rock;
}

ResourceCounter::~ResourceCounter() {
	// TODO Auto-generated destructor stub
}

