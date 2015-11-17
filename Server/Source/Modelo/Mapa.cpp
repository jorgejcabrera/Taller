/*
 * Mapa.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/Mapa.h"

Mapa::Mapa() {
	this->gameSettings = GameSettings::GetInstance();
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
		this->getTileAt(posX,posY)->setSuperficie((*it).second);
	}

	//creamos recursos de manera ramdom
	this->createResources();
}

void Mapa::createResources(){
	unsigned int maxResources = 10;
	//genramos una posicion random
	int height = this->gameSettings->getMapHeight();
	int width = this->gameSettings->getMapWidth();
	int x = rand() % width;
	int y = rand() % height;
	//generamos un tipo de recurso random
	int tipo = ( rand() % 4 + 1);
	Resource* newResource = NULL;

	while( this->resources.size() < maxResources ){
		if( this->tiles.at(make_pair(x,y))->isAvailable() ){
			if( tipo == 1 ){
				newResource = new Resource("gold",x,y);
				newResource->setNotifiable(true);
				this->tiles.at(make_pair(x,y))->changeStatusAvailable();
			
			}else if( tipo == 2 ){
				newResource = new Resource("food",x,y);
				newResource->setNotifiable(true);
				this->tiles.at(make_pair(x,y))->changeStatusAvailable();
			
			}else if( tipo == 3 ){
				newResource = new Resource("wood",x,y);
				newResource->setNotifiable(true);
				this->tiles.at(make_pair(x,y))->changeStatusAvailable();
			
			}else if( tipo == 4 ){
				newResource = new Resource("rock",x,y);
				newResource->setNotifiable(true);
				this->tiles.at(make_pair(x,y))->changeStatusAvailable();
			}
			this->resources.push_front(newResource);
		}
		x = rand() % width;
		y = rand() % height;
		tipo = ( rand() % 4 + 1);
	}
}

list<Message*> Mapa::getResourcesMessages(){
	list<Message*> news;
	Message* msg = NULL;
	for(list<Resource*>::iterator it = this->resources.begin(); it != this->resources.end(); ++it){
		Logger::get()->logDebug("Mapa","getNewsResources","agregamos un recurso para que sea notificado");
		msg = new Message();
		msg->setId((*it)->getId());
		msg->setName((*it)->getName());
		msg->setType("newResource");
		msg->setPosition((*it)->getPosition());
		news.push_front(msg);
	}
	return news;
}

void Mapa::deleteEntity(int id){
	for(list<Resource*>::iterator it = this->resources.begin() ; it!=this->resources.end();++it){
		if( (*it)->getId() == id ){
			this->resources.erase(it);
			return;
		}
	}
	for(list<EntidadPartida*>::iterator itEntity = this->entidades.begin(); itEntity!=this->entidades.end();++itEntity){
		if( (*itEntity)->getId() == id ){
			this->entidades.erase(itEntity);
			return;
		}
	}
}

list<Resource*>* Mapa::getResources(){
	return &this->resources;
}


void Mapa::pushEntity(EntidadPartida* entidad){
	stringstream ss;
	if(!this->positionAvailable(entidad)){
		ss << entidad->getName() << " can't push entity in " << entidad->getPosition().first <<" "<< entidad->getPosition().second;
		Logger::get()->logError("Mapa","pushEntity",ss.str());
		return;
	}else{
		pair<int,int> lowerVertex = make_pair(entidad->getPosition().first+ entidad->getWidth(), entidad->getPosition().second + entidad->getLength());
		this->entidades.push_back(entidad);
		//le cambiamos el estado a los tiles que ocupa la entidad
		for(int j=entidad->getPosition().second; j<lowerVertex.second; j++)
			for(int i=entidad->getPosition().first; i<lowerVertex.first; i++){
				this->tiles.at(make_pair(i,j))->changeStatusAvailable();
			}
		return;
	}
}

bool Mapa::positionAvailable(EntidadPartida* entidad){
	stringstream ss;
	int x = entidad->getPosition().first;
	int y = entidad->getPosition().second;
	if( x > gameSettings->getMapWidth() || y > gameSettings->getMapHeight() || x < 0 || y < 0){
		return false;
	}
	int posFinalX = x + entidad->getWidth();
	int posFinalY = y + entidad->getLength();
	if( posFinalX > gameSettings->getMapWidth() || posFinalY > gameSettings->getMapHeight())
		return false;
	if(!this->tiles.at(make_pair(x,y))->isAvailable() || !this->tiles.at(make_pair( x + entidad->getWidth()-1, y + entidad->getLength()-1))->isAvailable() ){
		ss << entidad->getName() << " can't push entity in " << entidad->getPosition().first <<" "<< entidad->getPosition().second <<" width "<<  entidad->getWidth()<< " LENGTH "<< entidad->getLength();
		ss << " " <<this->tiles.at(make_pair(x,y))->isAvailable()<< " " << this->tiles.at(make_pair( x + entidad->getWidth()-1, y + entidad->getLength()-1))->isAvailable();
		Logger::get()->logError("Mapa","positionAvailable",ss.str());
		return false;
	}
	return true;
}

Tile* Mapa::getTileAt(int x,int y){
	return this->tiles.at(make_pair(x,y));
}

//Busco una posicion disponible para poner un personaje cuando se crea un cliente
pair<int,int> Mapa::getAvailablePosition(){
	for(map<pair<int,int>,Tile*>::iterator tilesIterator=this->tiles.begin(); tilesIterator!=this->tiles.end(); ++tilesIterator){
		if(tilesIterator->second->isAvailable()){
			return tilesIterator->first;
		}
	}
	return make_pair(-1,-1);
}

pair<int,int> Mapa::getAvailablePosition(int xFrom, int yFrom){
	bool positionFound = false;
	for(map<pair<int,int>,Tile*>::iterator tilesIterator = this->tiles.begin(); tilesIterator != this->tiles.end(); ++tilesIterator){
		if ((tilesIterator->second->getPosX() == xFrom && tilesIterator->second->getPosY() == yFrom) || positionFound ){
			positionFound=true;
			if(tilesIterator->second->isAvailable() && abs(tilesIterator->second->getPosX()-xFrom)<10 && abs(tilesIterator->second->getPosY()-yFrom)<10){
				return tilesIterator->first;
			}
		}
	}
	return make_pair(-1,-1);
}

map<pair<int,int>,Tile*>* Mapa::getTiles(){
	return &this->tiles;
}

list<EntidadPartida*>* Mapa::getEntities(){
	return &this->entidades;
}	

Mapa::~Mapa() {
	for (list<EntidadPartida*>::iterator it=this->entidades.begin(); it!=this->entidades.end(); ++it){
		delete((*it));
	}
	for (map<pair<int,int>,Tile*>::iterator it=this->tiles.begin(); it!=this->tiles.end(); ++it){
		delete((*it).second);
		(*it).second = NULL;
	}
	this->gameSettings=NULL;
}

