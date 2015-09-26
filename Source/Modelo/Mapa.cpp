/*
 * Mapa.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "Mapa.h"

Mapa::Mapa() {
	gameSettings = GameSettings::GetInstance();
	//barrido vertical del mapa
	for(int i = 0; i < gameSettings->getMapHeight(); i++){
		//barrido horizontal del mapa
		for(int j = 0; j < gameSettings->getMapWidth(); j++){
			Tile* newTile =  new Tile(j,i);
			this->tiles.insert(std::make_pair(std::make_pair(j,i),newTile));
		}
	}

	list<EntidadPartida*> edificios = gameSettings->getEntidadesEstaticas();
	for(list<EntidadPartida*>::iterator it=edificios.begin(); it!=edificios.end(); ++it){
		this->pushEntity(*it);
	}

	map<pair<int,int>,string> tilesToSetImage = gameSettings->getTiles();
	for (std::map<pair<int,int>,string>::iterator it = tilesToSetImage.begin(); it != tilesToSetImage.end();++it){
		int posX = (*it).first.first;
		int posY = (*it).first.second;
		this->getTileAt(posX,posY)->setPathImage((*it).second);
	}
}

void Mapa::pushEntity(EntidadPartida* entidad){
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
	if( x > gameSettings->getMapWidth() || y > gameSettings->getMapHeight() || x < 0 || y < 0)
		return false;
	int posFinalX = x + entidad->getWidth();
	int posFinalY = y + entidad->getLength();
	if( posFinalX > gameSettings->getMapWidth() || posFinalY > gameSettings->getMapHeight())
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
		 // cout<< (*it).first.first << ";" << (*it).first.second << " => ";
		  (*it).second->show();
	}
	return;
}

Mapa::~Mapa() {
	for (map<pair<int,int>,EntidadPartida*>::iterator it=this->entidades.begin(); it!=this->entidades.end(); ++it){
//		(*it).second->~EntidadPartida();
		delete((*it).second);
		(*it).second = NULL;
	}
	for (map<pair<int,int>,Tile*>::iterator it=this->tiles.begin(); it!=this->tiles.end(); ++it){
//		(*it).second->~Tile();
		delete((*it).second);
		(*it).second = NULL;
	}
	this->gameSettings=NULL;
}

