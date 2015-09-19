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
	this->event = new SDL_Event();
	this->posMouseX = 0;
	this->posMouseY = 0;
	this->inicioDeCiclo = 0;
}

Juego* GameController::getJuego(){
	return this->juego;
}

void GameController::obtenerMouseInput(){

	while(SDL_PollEvent(event)){

		if( event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT){
			SDL_GetMouseState(&posMouseX,&posMouseY);
			cout << "clickeamos en :"<< posMouseX << "," << posMouseY <<endl;
			this->moveCharacter(posMouseX,posMouseY);
		}
		if( event->type == SDL_QUIT)
			this->salirDelJuego = true;
		if( event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_r)
			this->reiniciar = true;

	}
}

void GameController::actualizarJuego(){
	juego->actualizarProtagonista();
	pair<int,int> offset = this->getOffset(this->juego->getOffset()->first,this->juego->getOffset()->second);
	/*pair<int,int> offset;
	offset.first = 0;
	offset.second = 0;*/
	juego->actualizarOffset(offset.first,offset.second);
}

bool GameController::reiniciarJuego(){
	return this->reiniciar;
}

bool GameController::finDeJuego(){
	this->inicioDeCiclo = SDL_GetTicks();
	return (event->type == SDL_QUIT || event->type == SDL_WINDOWEVENT_CLOSE);
}

pair<int,int> GameController::getOffset(int offSetX, int offSetY){
	int posicionX = 0;
	int posicionY = 0;
	SDL_GetMouseState(&posicionX, &posicionY);

	if (posicionX >= DefaultSettings::getMargenDerechoUno() && posicionX < DefaultSettings::getMargenDerechoDos() /*&& !(offSetX < DefaultSettings::getLimiteDerecho())*/) {
		offSetX -= DefaultSettings::getVelocidadScrollUno();
	}
	if (posicionX >= DefaultSettings::getMargenDerechoDos() /*&& !(offSetX < DefaultSettings::getLimiteDerecho())*/) {
		offSetX -= 1 * DefaultSettings::getVelocidadScrollDos();
	}
	if ((posicionX >= DefaultSettings::getMargenIzquierdoUno()) && (posicionX < DefaultSettings::getMargenIzquierdoDos()) /*&& !(offSetX > DefaultSettings::getLimiteIzquierdo())*/) {
		offSetX += DefaultSettings::getVelocidadScrollUno();
	}
	if (posicionX <= DefaultSettings::getMargenIzquierdoDos() /*&& !(offSetX > DefaultSettings::getLimiteIzquierdo())*/) {
		offSetX += DefaultSettings::getVelocidadScrollDos();
	}
	if ((posicionY <= DefaultSettings::getMargenSuperiorUno()) && (posicionY > DefaultSettings::getMargenSuperiorDos()) /*&& !((offSetY > DefaultSettings::getLimiteSuperior()))*/) {
		offSetY += DefaultSettings::getVelocidadScrollUno();
	}
	if (posicionY <= DefaultSettings::getMargenSuperiorDos() /*&& !((offSetY > DefaultSettings::getLimiteSuperior()))*/) {
		offSetY += DefaultSettings::getVelocidadScrollDos();
	}
	if (posicionY >= DefaultSettings::getMargenInferiorUno() && (posicionY < DefaultSettings::getMargenInferiorDos()) /*&& !((offSetY < DefaultSettings::getLimiteInferior()))*/) {
		offSetY -= DefaultSettings::getVelocidadScrollUno();
	}
	if ((posicionY >= DefaultSettings::getMargenInferiorDos()) /*&& !((offSetY < DefaultSettings::getLimiteInferior()))*/) {
		offSetY -= DefaultSettings::getVelocidadScrollDos();
	}
	pair<int,int> curretOffset;
	curretOffset.first = offSetX;
	curretOffset.second = offSetY;
	return curretOffset;
}

void GameController::moveCharacter(int xScreen,int yScreen){
	pair<int,int>* offset = this->juego->getOffset();
	cout << "offset " << offset->first << ","<<offset->second<<endl;
	pair<int,int> cartesianPosition = this->utils->convertToCartesian(xScreen+offset->first,yScreen+offset->second);
	bool correctPosition = false;

	cout << "la coordenada cartesiana es: " << cartesianPosition.first << "," << cartesianPosition.second<<endl;
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
	cout << "la coordenada cartesiana es: " << cartesianPosition.first << "," << cartesianPosition.second<<endl;


	//si tuvimos que hacer alguna correccion cambiamos la posicion final del mouse
	if(correctPosition){
		pair<int,int> isometricPosition = this->utils->getIsometricPosition(cartesianPosition.first,cartesianPosition.second);
		posMouseX = isometricPosition.first;
		posMouseY = isometricPosition.second;
	}

	//una vez convertida a cartesiana la posicion le decimos al modelo que se actualize
	juego->setDestinoProtagonista(cartesianPosition.first,cartesianPosition.second,posMouseX,posMouseY);
	//cout << "posicion del personaje: " << cartesianPosition.first << ";" << cartesianPosition.second<<endl;
	//cout << "screen position: "<< juego->getProtagonista()->getScreenPosition()->first<<";"<<juego->getProtagonista()->getScreenPosition()->second<<endl;
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
	delete event;
}

