/*
 * ResourceManager.cpp
 *
 *  Created on: Oct 17, 2015
 *      Author: juan
 */

#include "../../Headers/Modelo/ResourceManager.h"

ResourceManager::ResourceManager(Mapa* map){
	int cantidadInicial = 10;
	this->alimento = cantidadInicial;
	this->madera = cantidadInicial;
	this->oro = cantidadInicial;

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
	bool collected = false;
	for (list<Resource*>::iterator it=this->resources->begin(); it != this->resources->end() && ! collected; ++it)
		if((*it)->getPosition()->first == pos->first && (*it)->getPosition()->second == pos->second){
			if((*it)->getTipo() == "chori") this->alimento++;
			if((*it)->getTipo() == "gold") this->oro++;
			if((*it)->getTipo() == "wood") this->madera++;
			this->resources->erase(it);
			collected = true;
		}

	std::map<pair<int,int>,EntidadPartida*>::iterator it2;
	it2 = map->getEntities()->find(*pos);
	if( it2 != map->getEntities()->end())
		map->getEntities()->erase(it2);

	cout<<"madera: "<<madera<<endl;
	cout<<"oro: "<<oro<<endl;
	cout<<"alimento: "<<alimento<<endl;

}

int ResourceManager::getFood(){
	return this->alimento;
}

int ResourceManager::getGold(){
	return this->oro;
}

int ResourceManager::getWood(){
	return this->madera;
}

ResourceManager::~ResourceManager() {
	resources->clear();
	delete resources;
}

