/*
 * ResourceManager.cpp
 *
 *  Created on: Oct 17, 2015
 *      Author: juan
 */

#include "ResourceManager.h"

ResourceManager::ResourceManager() {
	// TODO Auto-generated constructor stub

}

ResourceManager::ResourceManager(Mapa* map){
	this->map = map;
	this->resource = new Resource(15,8);
	this->map->pushEntity(this->resource);
}

bool ResourceManager::resourceAt(int x,int y){
	bool hay = false;
	if(resource->getPosition()->first == x && resource->getPosition()->second == y)
		hay = true;
	return hay;
}

ResourceManager::~ResourceManager() {
	// TODO Auto-generated destructor stub
}

