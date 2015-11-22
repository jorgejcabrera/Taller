/*
 * ResourceCounter.cpp
 *
 *  Created on: Oct 28, 2015
 *      Author: juan
 */

#include "../../Headers/Modelo/ResourceCounter.h"

ResourceCounter::ResourceCounter() {
	int cantInicial = 10000;
	this->food = cantInicial;
	this->gold = cantInicial;
	this->wood = cantInicial;
	this->rock = cantInicial;
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
		this->gold += quantity;
	if(recurso == "wood")
		this->wood += quantity;
	if(recurso == "food")
		this->food += quantity;
	if(recurso == "rock")
		this->rock += quantity;
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

