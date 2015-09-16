/*
 * GameController.cpp
 *
 *  Created on: Sep 11, 2015
 *      Author: juan
 */

#include "GameController.h"

GameController::GameController(){

	this->salirDelJuego = false;

	this->juego = new Juego();
	this->juegoVista = new JuegoVista(juego);

	this->event = new SDL_Event();

	this->posMouseX = 0;
	this->posMouseY = 0;
}

void GameController::obtenerMouseInput(){

	while(SDL_PollEvent(event)){

		if( event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_RIGHT){
			SDL_GetMouseState(&posMouseX,&posMouseY);
			//TODO si la posicion está por fuera del mapa, dejar que se mueva hasta el borde.
			pair<int,int> cartesianPosition = this->convertToCartesian(posMouseX,posMouseX);
			//una vez convertida a cartesiana la posicion le decimos al modelo que se actualize
			juego->setDestinoProtagonista(cartesianPosition.first,cartesianPosition.second,posMouseX,posMouseY);
			juegoVista->protagonistaYaSeMovio();
		}

		if( event->type == SDL_QUIT) this->salirDelJuego = true;

	}
}

void GameController::actualizarJuego(){
	juego->actualizarProtagonista();
}

bool GameController::finDeJuego(){
	return (event->type == SDL_QUIT || event->type == SDL_WINDOWEVENT_CLOSE);
}

void GameController::render(){
	juegoVista->render();
}

pair<int,int> GameController::convertToCartesian(int xScreen,int yScreen){
	//TODO agregar lógica para ver si el chabón se quiere mover por fuera del mapa que lo deje llegar hasta el borde
	int startMapX = DefaultSettings::getScreenWidth() / 2 + DefaultSettings::getTileSize();
	int x = ( yScreen * 2 + xScreen - startMapX) / (DefaultSettings::getTileSize() * 2);
	int y = yScreen / (DefaultSettings::getTileSize() / 2) - x;
	pair<int,int> cartesianPosition;
	cartesianPosition.first = x;
	cartesianPosition.second = y;
	return cartesianPosition;
}


GameController::~GameController() {

	juego->~Juego();
	juegoVista->~JuegoVista();

	delete event;
}

