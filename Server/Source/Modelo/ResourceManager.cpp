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

void ResourceManager::actualizar(){

	int nRandom = rand() % 18;

	//posicion random para el nuevo rescurso
	GameSettings* gs = GameSettings::GetInstance();
	int size = gs->getMapHeight();
	int x = rand() % size;
	int y = rand() % size;

	//tipo de recurso random
	int tipo = (rand()%3 + 1);

	if(this->map->getTileAt(x,y)->isAvailable() && nRandom == 0){
		Resource* nuevoRecurso;
		if(tipo == 1)
			nuevoRecurso = new Resource("gold",x,y);
		if(tipo == 2)
			nuevoRecurso = new Resource("chori",x,y);
		if(tipo == 3)
			nuevoRecurso = new Resource("wood",x,y);

		this->resources->push_front(nuevoRecurso);
		this->map->pushEntity(nuevoRecurso);
	}
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

