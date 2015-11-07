/*
 * GameController.cpp
 *
 *  Created on: Sep 11, 2015
 *      Author: juan
 */

#include "../../Headers/Control/GameController.h"

GameController::GameController(){
	this->gameSettings = GameSettings::GetInstance();
	this->utils = UtilsController::GetInstance();
	this->salirDelJuego = false;
	this->juego = new Juego();
	this->runCycles = 0;
	this->maxFramesPerSecond = 50; // maxima cantidad de frames del juego principal
}

Juego* GameController::getJuego(){
	return this->juego;
}

list<Message*> GameController::getTilesMessages(){
	list<Message*> listaDeTiles;
	map<pair<int,int>,Tile*>* tilesList = this->juego->getMap()->getTiles();
	for(map<pair<int,int>,Tile*>::iterator it=tilesList->begin(); it!=tilesList->end(); ++it){
		Message *tileMessage = new Message("tile",it->second->getSuperficie(),it->first.first,it->first.second);
		listaDeTiles.push_back(tileMessage);
	}
	return listaDeTiles;
}

list<Message*> GameController::getEntitiesMessages(){
	list<Message*> listaDeEntities;
	list<EntidadPartida*>* entidades = this->getJuego()->getMap()->getEntities();
	for(list<EntidadPartida*>::iterator it=entidades->begin(); it!=entidades->end();++it){
		string tipoEntidad = DefaultSettings::getTypeEntity((*it)->getName());
		//TODO revisar, las entidades tambien van a pertener a un cliente con lo cual tambien deberiamos mandar si el dueño está conectado o no. Seteo el ultimo parametro en 0 para simular que el dueño está conectado
		Message *entityMessage = new Message((**it).getId(), tipoEntidad, (**it).getName(), (**it).getPosition()->first, (**it).getPosition()->second, 0);
		entityMessage->setOwner((**it).getOwner());
		listaDeEntities.push_back(entityMessage);
	}
	return listaDeEntities;
}

list<int> GameController::getEntitiesOfClient(string userName){
	list<int> idOfEntities;
	map<int,EntidadDinamica*> listaPersonajes = this->juego->getProtagonistas();
	for(map<int,EntidadDinamica*>::iterator iteratePersonajes= listaPersonajes.begin(); iteratePersonajes!=listaPersonajes.end();++iteratePersonajes){
		if(iteratePersonajes->second->getOwner()==userName){
			idOfEntities.push_back(iteratePersonajes->first);
		}
	}
	return idOfEntities;
}

void GameController::setNextPaths(){
	//antes de setear el proximo path, me fijo si hay un recurso en donde esta

	map<int,EntidadDinamica*> listaPersonajes = this->juego->getProtagonistas();
	for(map<int,EntidadDinamica*>::iterator it = listaPersonajes.begin(); it!=listaPersonajes.end();++it){
		pair<int,int>* pos = (*it).second->getPosition();
		if( ! (*it).second->isWalking() && this->juego->getResourceManager()->resourceAt(pos->first,pos->second)){
			this->juego->getResourceManager()->collectResourceAt(pos);
			this->juego->getResourceManager()->setUltimoEnConsumir((*it).second->getOwner());
		}
		
		//pongo el tile anterior disponible
		pair<int,int>* firstPosition = (*it).second->getPosition();
		this->juego->getMap()->getTileAt(firstPosition->first,firstPosition->second)->setToAvailable();
		//busco la nueva posicion
		(*it).second->nextPosition();
		//pongo el nuevo tile como ocupado
		pair<int,int>* newPos = (*it).second->getPosition();
		this->juego->getMap()->getTileAt(newPos->first,newPos->second)->setToNotAvailable();

	}
}

void GameController::actualizarJuego(){
	this->setNextPaths();
	this->juego->getResourceManager()->actualizar();
}

int GameController::getRunCycles(){
	return this->runCycles;
}

int GameController::getMaxFramesPerSecond(){
	return this->maxFramesPerSecond;
}

void GameController::delay(){
	this->runCycles++;
	SDL_Delay(50); // para que sean 50 frames x segundos
}

void GameController::delay(int ms){
	this->runCycles++;
	SDL_Delay(ms);
}

GameController::~GameController() {
	//No ejecuto el destructor de juego porque lo hace el juegoVista
	this->juego=NULL;
//	this->utils->~UtilsController();
	delete(this->utils);
	this->utils = NULL;
//	this->gameSettings->~GameSettings();
	delete(this->gameSettings);
	this->gameSettings = NULL;
}
