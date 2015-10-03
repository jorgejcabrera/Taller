/*
 * GameController.cpp
 *
 *  Created on: Sep 11, 2015
 *      Author: juan
 */

#include "../../Headers/Control/GameController.h"

GameController::GameController(){
	gameSettings = GameSettings::GetInstance();
	this->utils = UtilsController::GetInstance();
	this->salirDelJuego = false;
	this->reiniciar = false;
	this->juego = new Juego();
	this->event = new SDL_Event();
	this->posMouseX = 0;
	this->posMouseY = 0;
	this->runCycles = 0;
	this->maxFramesPerSecond = 50; // maxima cantidad de frames del juego principal
}

Juego* GameController::getJuego(){
	return this->juego;
}

void GameController::obtenerMouseInput(){

	while(SDL_PollEvent(event)){

		if( event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT){
			SDL_GetMouseState(&posMouseX,&posMouseY);
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
	juego->actualizarOffset(offset.first,offset.second);
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

bool GameController::finDeJuego(){
	this->inicioDeCiclo = SDL_GetTicks();
	return (event->type == SDL_QUIT || event->type == SDL_WINDOWEVENT_CLOSE);
}

pair<int,int> GameController::getOffset(int offSetX, int offSetY){
	int posicionX = 0;
	int posicionY = 0;
	SDL_GetMouseState(&posicionX, &posicionY);

	if (posicionX >= gameSettings->getMargenDerechoUno()	&& posicionX < gameSettings->getMargenDerechoDos() && !(offSetX < gameSettings->getLimiteDerecho())) {
			offSetX -= gameSettings->getVelocidadScrollUno();
	}

	if (posicionX >= gameSettings->getMargenDerechoDos() && !(offSetX < gameSettings->getLimiteDerecho())) {
			offSetX -= 1 * gameSettings->getVelocidadScrollDos();
	}

	if ((posicionX > gameSettings->getMargenIzquierdoDos()) && (posicionX <= gameSettings->getMargenIzquierdoUno()) && !(offSetX > gameSettings->getLimiteIzquierdo())) {
			offSetX += gameSettings->getVelocidadScrollUno();
	}

	if (posicionX <= gameSettings->getMargenIzquierdoDos() && !(offSetX > gameSettings->getLimiteIzquierdo())) {
			offSetX += gameSettings->getVelocidadScrollDos();
	}

	if ((posicionY <= gameSettings->getMargenSuperiorUno()) && (posicionY > gameSettings->getMargenSuperiorDos()) && !((offSetY > gameSettings->getLimiteSuperior()))) {
			offSetY += gameSettings->getVelocidadScrollUno();
	}

	if (posicionY <= gameSettings->getMargenSuperiorDos() && !((offSetY > gameSettings->getLimiteSuperior()))) {
		offSetY += gameSettings->getVelocidadScrollDos();
	}

	if (posicionY >= gameSettings->getMargenInferiorUno() && (posicionY < gameSettings->getMargenInferiorDos()) && !((offSetY < gameSettings->getLimiteInferior()))) {
			offSetY -= gameSettings->getVelocidadScrollUno();
	}

	if ((posicionY >= gameSettings->getMargenInferiorDos()) && !((offSetY < gameSettings->getLimiteInferior()))) {
		offSetY -= gameSettings->getVelocidadScrollDos();
	}

	pair<int,int> curretOffset;
	curretOffset.first = offSetX;
	curretOffset.second = offSetY;
	return curretOffset;
}

void GameController::moveCharacter(int xScreen,int yScreen){
	pair<int,int>* offset = this->juego->getOffset();
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
}

void GameController::delay(){
	//if((SDL_GetTicks()-this->inicioDeCiclo) < 1000 / this->juego->getProtagonista()->getFramesPerSecond()){
		//int valor = ((1000 / this->juego->getProtagonista()->getFramesPerSecond()) - (SDL_GetTicks()-this->inicioDeCiclo));
		//SDL_Delay(valor);
	this->runCycles++;
	//if(this->runCycles % this->maxFramesPerSecond == 0){ this->runCycles = 0; }

	SDL_Delay(50); // para que sean 50 frames x segundos
	//}
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
	this->event->quit;
	delete(this->event);
	this->event = NULL;


}

