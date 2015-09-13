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
			std::cout<<posMouseX<<std::endl;
			juego->setDestinoProtagonista(posMouseX,posMouseY);
		}

		if( event->type == SDL_QUIT) this->salirDelJuego = true;

	}
}

void GameController::actualizarJuego(){

	juego->actualizarProtagonista();
}

bool GameController::finDeJuego(){
	//std::cout<<"loop"<<std::endl;
	return (event->type == SDL_QUIT || event->type == SDL_WINDOWEVENT_CLOSE);
}

void GameController::render(){
	juegoVista->render();
	juegoVista->renderProtagonista();
}

GameController::~GameController() {

	juego->~Juego();
	juegoVista->~JuegoVista();

	delete event;
}

