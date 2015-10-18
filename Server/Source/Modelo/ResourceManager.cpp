/*
 * ResourceManager.cpp
 *
 *  Created on: Oct 17, 2015
 *      Author: juan
 */

#include "../../Headers/Modelo/ResourceManager.h"

ResourceManager::ResourceManager(Mapa* map){
	this->map = map;
	this->resources = new list<Resource*>();
	Resource* oro = new Resource("gold",15,8);
	Resource* chori = new Resource("chori",11,9);
	Resource* madera = new Resource("wood",20,15);

	this->resources->push_front(oro);
	this->map->pushEntity(oro);
	this->resources->push_front(chori);
	this->map->pushEntity(chori);
	this->resources->push_front(madera);
	this->map->pushEntity(madera);
}

bool ResourceManager::resourceAt(int x,int y){
	bool hay = false;

	for (list<Resource*>::iterator it=this->resources->begin(); it != this->resources->end(); ++it)
	    if((*it)->getPosition()->first == x && (*it)->getPosition()->second == y)
	    	hay = true;
	return hay;
}

void ResourceManager::collectResourceAt(pair<int,int>* pos){
	std::map<pair<int,int>,EntidadPartida*>::iterator it;
	it = map->getEntities()->find(*pos);
	if( it != map->getEntities()->end())
		map->getEntities()->erase(it);
}

ResourceManager::~ResourceManager() {
	resources->clear();
	delete resources;
}

