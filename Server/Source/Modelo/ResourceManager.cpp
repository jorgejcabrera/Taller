/*
 * ResourceManager.cpp
 *
 *  Created on: Oct 17, 2015
 *      Author: juan
 */

#include "../../Headers/Modelo/ResourceManager.h"

ResourceManager::ResourceManager(Mapa* map){
	this->map = map;
	this->resource = new Resource("gold",15,8);
	this->map->pushEntity(this->resource);
}

bool ResourceManager::resourceAt(int x,int y){
	bool hay = false;
	if(resource->getPosition()->first == x && resource->getPosition()->second == y)
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
	// TODO Auto-generated destructor stub
}

