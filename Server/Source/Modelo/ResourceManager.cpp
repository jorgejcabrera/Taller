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
	Resource* oro = new Resource("gold",0,1);
	Resource* chori = new Resource("chori",1,0);
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

	//borro el recurso de la lista de recursos y sumo al contador
	for (list<Resource*>::iterator it=this->resources->begin(); it != this->resources->end() && ! collected; ++it)
		if((*it)->getPosition()->first == pos->first && (*it)->getPosition()->second == pos->second){
			if((*it)->getName() == "chori") this->alimento++;
			if((*it)->getName() == "gold") this->oro++;
			if((*it)->getName() == "wood") this->madera++;
			this->resources->erase(it);
			collected = true;
		}

	//borro el recurso del mapa
	list<EntidadPartida*>::iterator it2;
	for( it2 = this->map->getEntities()->begin(); it2 != this->map->getEntities()->end(); ++it2){
		if((*it2)->getPosition()->first == pos->first && (*it2)->getPosition()->second == pos->second){
			this->map->getEntities()->erase(it2);
		}
	}

	//marco el tile como disponible
	map->getTileAt(pos->first,pos->second)->changeStatusAvailable();

	cout<<"madera: "<<madera<<endl;
	cout<<"oro: "<<oro<<endl;
	cout<<"alimento: "<<alimento<<endl;

}

//despues lo ponemos
/*
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
}*/

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
