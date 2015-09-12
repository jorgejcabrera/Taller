/*
 * GameController.cpp
 *
 *  Created on: Sep 11, 2015
 *      Author: juan
 */

#include "GameController.h"

GameController::GameController(){

	this->juego = new Juego();
	this->juegoVista = new JuegoVista(juego);

	this->protagonista = new EntidadDinamica(5,300,300);
	string imgPath = "../Taller/Images/ricardo.png";

	this->event = new SDL_Event();

	this->posMouseX = 0;
	this->posMouseY = 0;

}

void GameController::obtenerMouseInput(){

	SDL_PollEvent(event);

	if(event->type == SDL_QUIT) std::cout<<"cerrar"<<std::endl;

	if( event->type == SDL_MOUSEBUTTONDOWN) if (event->button.button == SDL_BUTTON_RIGHT){

		SDL_GetMouseState(&posMouseX,&posMouseY);

		std::cout<<posMouseX<<std::endl;

		// aca le tengo que decir al juego que actualice al protragonista
	}
}

bool GameController::finDeJuego(){

	std::cout<<"loop"<<std::endl;
	return (event->type == SDL_QUIT);
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

