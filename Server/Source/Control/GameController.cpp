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
		Message *entityMessage = new Message((**it).getId(), tipoEntidad, (**it).getName(), (**it).getPosition()->first, (**it).getPosition()->second);
		listaDeEntities.push_back(entityMessage);
	}
	return listaDeEntities;
}

list<Message*> GameController::getProtagonistasMessages(){
	list<Message*> listaDeProtagonistas;
		map<int,EntidadDinamica*> protagonistas = this->getJuego()->getProtagonistas();
		for(map<int,EntidadDinamica*>::iterator it=protagonistas.begin(); it!=protagonistas.end();++it){
			string tipoEntidad = DefaultSettings::getTypeEntity((*it).second->getName());
			//TODO ver como hacemos para mandar el nombre porque hoy en dia si le ponemos "Cliente 1" va a romper porque no va a encontrar el tipo de entidad
			Message *protagonistaMessage = new Message((*it).second->getId(), tipoEntidad, (*it).second->getName(), (*it).second->getPosition()->first, (*it).second->getPosition()->second);
			//cout << "ENTIDAD: " << protagonistaMessage->toString()<<endl;
			listaDeProtagonistas.push_back(protagonistaMessage);
		}
		return listaDeProtagonistas;
}

void GameController::actualizarJuego(){
	//TODO: el offset no deberia necesitarlo porqeu es un tema de la vista
	juego->actualizarProtagonistas();
	//pair<int,int> offset = this->getOffset(this->juego->getOffset()->first,this->juego->getOffset()->second);
	//juego->actualizarOffset(offset.first,offset.second);
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


void GameController::moveCharacter(int xScreen,int yScreen){
	//TODO: aca deberiamos actualizar la posicion del personaje con las coordenadas que me llegan. Deberian llegar sin el offset
	/*pair<int,int>* offset = this->juego->getOffset();
	pair<int,int> cartesianPosition = this->utils->convertToCartesian(xScreen-offset->first,yScreen-offset->second);
	bool correctPosition = false;

	//las coordenadas cartesianas siempre tienen que quedar dentro del mapa
	if( cartesianPosition.first < 0 ){
		cartesianPosition.first = 0;
		correctPosition = true;
	}else if( cartesianPosition.first >= gameSettings->getMapWidth()){
		cartesianPosition.first = gameSettings->getMapWidth() - 1 ;
		correctPosition = true;
	}
	if( cartesianPosition.second < 0){
		cartesianPosition.second = 0;
		correctPosition = true;
	}else if( cartesianPosition.second >= gameSettings->getMapHeight()){
		cartesianPosition.second = gameSettings->getMapHeight() - 1;
		correctPosition = true;
	}

	//si tuvimos que hacer alguna correccion cambiamos la posicion final del mouse
	if(correctPosition){
		pair<int,int> isometricPosition = this->utils->getIsometricPosition(cartesianPosition.first,cartesianPosition.second);
		posMouseX = isometricPosition.first+offset->first;
		posMouseY = isometricPosition.second+offset->second;
	}

	//una vez convertida a cartesiana la posicion le decimos al modelo que se actualize
	juego->setDestinoProtagonista(cartesianPosition.first,cartesianPosition.second,posMouseX,posMouseY);
	return;
	*/
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

