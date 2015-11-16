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
	this->roca = cantidadInicial;

	this->notify = false;
	this->newResource = false;

	this->map = map;
	this->resources = new list<Resource*>();
	Resource* oro = new Resource("gold",14,16,10000);
	Resource* chori = new Resource("food",0,20,10000);
	Resource* madera = new Resource("wood",20,15,10000);

	this->resources->push_front(oro);
	this->map->pushEntity(oro);
	this->resources->push_front(chori);
	this->map->pushEntity(chori);
	this->resources->push_front(madera);
	this->map->pushEntity(madera);
}

bool ResourceManager::isResourceAt(int x,int y){
	bool hay = false;
	for (list<Resource*>::iterator it=this->resources->begin(); it != this->resources->end(); ++it){
	    if((*it)->getPosition().first == x && (*it)->getPosition().second == y)
	    	hay = true;
	}
	return hay;
}

void ResourceManager::collectResourceAt(pair<int,int>* pos){
	bool collected = false;

	//borro el recurso de la lista de recursos y sumo al contador
	for (list<Resource*>::iterator it=this->resources->begin(); it != this->resources->end() && ! collected; ++it)
		if((*it)->getPosition().first == pos->first && (*it)->getPosition().second == pos->second){
			this->IdRecursoAEliminar = (*it)->getId();
			if((*it)->getName() == "chori") setUltimoTipoConsumido("chori");
			if((*it)->getName() == "gold") setUltimoTipoConsumido("gold");
			if((*it)->getName() == "wood") setUltimoTipoConsumido("wood");
			if((*it)->getName() == "rock") setUltimoTipoConsumido("rock");
			this->resources->erase(it);
			collected = true;
		}

	//borro el recurso del mapa
	list<EntidadPartida*>::iterator it2;
	bool borrado = false;
	for( it2 = this->map->getEntities()->begin(); it2 != this->map->getEntities()->end() && ! borrado; ++it2){
		if((*it2)->getPosition().first == pos->first && (*it2)->getPosition().second == pos->second){
			this->map->getEntities()->erase(it2);
			borrado = true;
		}
	}

	//marco el tile como disponible
	map->getTileAt(pos->first,pos->second)->changeStatusAvailable();
	this->notify = true;
}

void ResourceManager::getNewResource(){

	unsigned int maxResources = 12;
	int nRandom = rand() % 30;

	//posicion random para el nuevo rescurso
	GameSettings* gs = GameSettings::GetInstance();
	int size = gs->getMapHeight();
	int x = rand() % size;
	int y = rand() % size;

	//tipo de recurso random
	int tipo = (rand()%4 + 1);

	if(this->map->getTileAt(x,y)->isAvailable() && nRandom == 0 && this->resources->size() < maxResources){
		Resource* nuevoRecurso;
		if(tipo == 1){
			nuevoRecurso = new Resource("gold",x,y,100);
			this->tipoUltimoCreado = "gold";
		}
		if(tipo == 2){
			nuevoRecurso = new Resource("chori",x,y,100);
			this->tipoUltimoCreado = "chori";
		}
		if(tipo == 3){
			nuevoRecurso = new Resource("wood",x,y,100);
			this->tipoUltimoCreado = "wood";
		}
		if(tipo == 4){
			nuevoRecurso = new Resource("rock",x,y,100);
			this->tipoUltimoCreado = "rock";
		}

		this->posNuevoRecurso.first = x;
		this->posNuevoRecurso.second = y;
		this->IdNuevoRecurso = nuevoRecurso->getId();


		this->resources->push_front(nuevoRecurso);
		this->map->pushEntity(nuevoRecurso);
		newResource = true;
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

bool ResourceManager::hasToNotify(){
	return this->notify;
}

void ResourceManager::yaNotifique(){
	this->notify = false;
}

int ResourceManager::getIdAEliminar(){
	return this->IdRecursoAEliminar;
}

int ResourceManager::getIdNuevoRecurso(){
	return this->IdNuevoRecurso;
}

void ResourceManager::setUltimoEnConsumir(string owner){
	this->ultimoEnConsumir = owner;
}

string ResourceManager::getUltimoEnConsumir(){
	return this->ultimoEnConsumir;
}

void ResourceManager::setUltimoTipoConsumido(string tipo){
	this->ultimoTipoConsumido = tipo;
}

string ResourceManager::getUltimoTipoConsumido(){
	return this->ultimoTipoConsumido;
}

bool ResourceManager::hasNewResource(){
	return this->newResource;
}

pair<int,int> ResourceManager::getPosNuevoRecurso(){
	return this->posNuevoRecurso;
}

string ResourceManager::getUltimoTipoCreado(){
	return this->tipoUltimoCreado;
}

void ResourceManager::newResourceSent(){
	this->newResource = false;
}

ResourceManager::~ResourceManager() {
	resources->clear();
	delete resources;
}
