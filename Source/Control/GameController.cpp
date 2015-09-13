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
			juego->setDestinoProtagonista(posMouseX,posMouseY);
			pair<float,float> result = this->convertToCartesian(posMouseX,posMouseY);
			cout <<"La posicion cartesiana es: " <<result.first << ","<< result.second<<endl;
		}

		if( event->type == SDL_QUIT) this->salirDelJuego = true;

	}
}

pair<float,float> GameController::convertToCartesian(int xScreen,int yScreen){
	cout<< "ScreenCoord: "<< xScreen<<","<< yScreen << endl;
	int startMapX = DefaultSettings::getScreenWidth() / 2 + DefaultSettings::getTileSize();
	float x = ( yScreen * 2 + xScreen - startMapX + DefaultSettings::getTileSize()) / (DefaultSettings::getTileSize() * 2);
	float y =  yScreen / (DefaultSettings::getTileSize() / 2) - x;
	pair<float,float> cartesianPosition;
	cartesianPosition.first = x;
	cartesianPosition.second = y;
	return cartesianPosition;
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

