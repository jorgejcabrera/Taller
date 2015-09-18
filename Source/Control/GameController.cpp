/*
 * GameController.cpp
 *
 *  Created on: Sep 11, 2015
 *      Author: juan
 */

#include "GameController.h"

GameController::GameController(){

	this->utils = UtilsController::GetInstance();

	this->salirDelJuego = false;
	this->reiniciar = false;

	this->juego = new Juego();
	this->juegoVista = new JuegoVista(juego);

	this->event = new SDL_Event();

	this->posMouseX = 0;
	this->posMouseY = 0;
	this->inicioDeCiclo = 0;
}

void GameController::obtenerMouseInput(){

	while(SDL_PollEvent(event)){

		if( event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT){
			SDL_GetMouseState(&posMouseX,&posMouseY);
			this->moveCharacter(posMouseX,posMouseY);
		}

		if( event->type == SDL_QUIT) this->salirDelJuego = true;

		if( event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_r) this->reiniciar = true;

	}
}

void GameController::actualizarJuego(){
	juego->actualizarProtagonista();
}

bool GameController::reiniciarJuego(){
	return this->reiniciar;
}

bool GameController::finDeJuego(){
	this->inicioDeCiclo = SDL_GetTicks();
	return (event->type == SDL_QUIT || event->type == SDL_WINDOWEVENT_CLOSE);
}

void GameController::render(){
	juegoVista->render();
}

void GameController::moveCharacter(int xScreen,int yScreen){
	pair<int,int> cartesianPosition = this->utils->convertToCartesian(xScreen,yScreen);
	bool correctPosition = false;

	//las coordenadas cartesianas siempre tienen que quedar dentro del mapa
	if( cartesianPosition.first < 0 ){
		cartesianPosition.first = 0;
		correctPosition = true;
	}else if( cartesianPosition.first >= DefaultSettings::getMapWidth()){
		cartesianPosition.first = DefaultSettings::getMapWidth() - 1 ;
		correctPosition = true;
	}
	if( cartesianPosition.second < 0){
		cartesianPosition.second = 0;
		correctPosition = true;
	}else if( cartesianPosition.second >= DefaultSettings::getMapHeight()){
		cartesianPosition.second = DefaultSettings::getMapHeight() - 1;
		correctPosition = true;
	}

	//si tuvimos que hacer alguna correccion cambiamos la posicion final del mouse
	if(correctPosition){
		pair<int,int> isometricPosition = this->utils->getIsometricPosition(cartesianPosition.first,cartesianPosition.second);
		posMouseX = isometricPosition.first;
		posMouseY = isometricPosition.second;
	}

	//una vez convertida a cartesiana la posicion le decimos al modelo que se actualize
	juego->setDestinoProtagonista(cartesianPosition.first,cartesianPosition.second,posMouseX,posMouseY);
	return;
}

void GameController::delay(){
	if((SDL_GetTicks()-this->inicioDeCiclo) < 1000 / this->juego->getProtagonista()->getFramesPerSecond()){
		int valor = ((1000 / this->juego->getProtagonista()->getFramesPerSecond()) - (SDL_GetTicks()-this->inicioDeCiclo));
		SDL_Delay(valor);
	}
}
GameController::~GameController() {
	juego->~Juego();
	juegoVista->~JuegoVista();
	delete event;
}

