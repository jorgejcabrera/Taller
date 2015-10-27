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
	this->reiniciar = false;
	this->juego = new Juego();
	this->posMouseX = 0;
	this->posMouseY = 0;
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

	map<int,EntidadDinamica*> listaPersonajes = this->juego->getProtagonistas();
	for(map<int,EntidadDinamica*>::iterator it= listaPersonajes.begin(); it!=listaPersonajes.end();++it){
		(*it).second->nextPosition();
	}
}

void GameController::actualizarJuego(){
	this->setNextPaths();
}

bool GameController::reiniciarJuego(){
	return this->reiniciar;
}

int GameController::getRunCycles(){
	return this->runCycles;
}

int GameController::getMaxFramesPerSecond(){
	return this->maxFramesPerSecond;
}

void GameController::delay(){
	//TODO: revisar si se puede sacar el delay, ya que de esa manera sacariamos el include de SDL2
	this->runCycles++;
	SDL_Delay(50); // para que sean 50 frames x segundos
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