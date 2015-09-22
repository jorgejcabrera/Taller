/*
 * Mapa.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "Mapa.h"

using namespace std;

Mapa::Mapa() {

	//barrido vertical del mapa
	for(int i = 0; i < DefaultSettings::getMapHeight(); i++){
		//barrido horizontal del mapa
		for(int j = 0; j < DefaultSettings::getMapWidth(); j++){
			Tile* newTile =  new Tile(j,i);
			this->tiles.insert(std::make_pair(std::make_pair(j,i),newTile));
		}
	}

	//TODO sacar esto. Creamos un par de entidades para probar
    /*EntidadEstatica* torre = new EntidadEstatica(DefaultSettings::getMediumSize(),DefaultSettings::getMediumSize(),"Church",true);
    torre->setPosition(0,0);
    this->pushEntity(torre);
	EntidadEstatica* castillo = new EntidadEstatica(DefaultSettings::getMediumSize(),DefaultSettings::getMediumSize(),"Consulate",true);
    castillo->setPosition(9,2);
    this->pushEntity(castillo);*/
    EntidadEstatica* edificio = new EntidadEstatica(DefaultSettings::getMediumSize(),DefaultSettings::getMediumSize(),"Town_Hall",true);
    edificio->setPosition(2,10);
    this->pushEntity(edificio);

    EntidadSemiEstatica* molino = new EntidadSemiEstatica(DefaultSettings::getMediumSize(),DefaultSettings::getMediumSize(),100,100,10,"molino");
    molino->setPosition(3,3);
    this->pushEntity(molino);
}

void Mapa::pushEntity(EntidadPartida* entidad){
	//pair<int,int>* position = entidad->getPosition();
	if(!this->positionAvailable(entidad)){
		cout << "no se puede colocar la entidad, en este tile"<<endl;
		return;
	}else{
		pair<int,int> lowerVertex = make_pair(entidad->getPosition()->first + entidad->getWidth(), entidad->getPosition()->second + entidad->getLength());
		int i=entidad->getPosition()->first;
		int j= entidad->getPosition()->second;
		this->entidades.insert(std::make_pair(std::make_pair(i,j),entidad));

		for(int j=entidad->getPosition()->second; j<lowerVertex.second; j++)
			for(int i=entidad->getPosition()->first; i<lowerVertex.first; i++)
				this->getTileAt(i,j)->changeStatusAvailable();

		return;
	}
}

bool Mapa::positionAvailable(EntidadPartida* entidad){
	int x = entidad->getPosition()->first;
	int y = entidad->getPosition()->second;
	if(!this->getTileAt(x,y)->isAvailable())
		return false;
	//TODO cambir esto por el ancho del y alto del mapa que lo tiene que tener el loader, que es quien parsea el YMAL
	if( x > DefaultSettings::getMapWidth() || y > DefaultSettings::getMapHeight() || x < 0 || y < 0)
		return false;
	return true;
}
EntidadPartida* Mapa::getEntityAt(int x,int y){
	return this->entidades.at(make_pair(x,y));
}

Tile* Mapa::getTileAt(int x,int y){
	return this->tiles.at(make_pair(x,y));
}

map<pair<int,int>,Tile*>* Mapa::getTiles(){
	return &this->tiles;
}

map<pair<int,int>,EntidadPartida*>* Mapa::getEntities(){
	return &this->entidades;
}

void Mapa::show(){
	for (std::map<pair<int,int>,Tile*>::iterator it = tiles.begin(); it != tiles.end();++it){
		  cout<< (*it).first.first << ";" << (*it).first.second << " => ";
		  (*it).second->show();
	}
	return;
}

Mapa::~Mapa() {
	for (map<pair<int,int>,EntidadPartida*>::iterator it=this->entidades.begin(); it!=this->entidades.end(); ++it){
		(*it).second->destruir();
	}
	for (map<pair<int,int>,Tile*>::iterator it=this->tiles.begin(); it!=this->tiles.end(); ++it){
		(*it).second->~Tile();
	}
}

