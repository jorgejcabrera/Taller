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
	this->juegoVista = new JuegoVista();
	this->salirDelJuego = false;
	this->event = new SDL_Event();
	this->posMouseX = 0;
	this->posMouseY = 0;
	this->runCycles = 0;
	this->maxFramesPerSecond = 50; // maxima cantidad de frames del juego principal
	this->gameRunning=false;
	this->idEntitySelected=0;
}

Message* GameController::getMessageFromEvent(string userName){

	while(SDL_PollEvent(event)){
		if( event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT){
			SDL_GetMouseState(&posMouseX,&posMouseY);
			if ( posMouseY >= gameSettings->getScreenHeight()-gameSettings->getAlturaMenuInferior() ){
				// TODO aca iria algo en caso de que el menu sea interactivo
			} else {
				if(this->idEntitySelected>0){
					EntidadDinamicaVista* miPersonaje = this->juegoVista->getEntityById(this->idEntitySelected);
					pair<int,int> cartesianPosition = this->moveCharacter(miPersonaje);
					Message* message = new Message();
					msg_game body;
					body.set_id(this->idEntitySelected);
					body.set_tipo("update");
					body.set_x(cartesianPosition.first);
					body.set_y(cartesianPosition.second);
					message->setContent(body);
					return message;
				}
			}
		}

		if( event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_RIGHT){
			SDL_GetMouseState(&posMouseX,&posMouseY);
			if ( posMouseY <= gameSettings->getScreenHeight()-gameSettings->getAlturaMenuInferior() ){
				pair<int,int>* offset = this->juegoVista->getOffset();
				pair<int,int> cartesianPosition = this->utils->convertToCartesian( this->posMouseX-offset->first, this->posMouseY-offset->second);
				map<string,string> entidadMap = juegoVista->entityInThisPosition(cartesianPosition.first, cartesianPosition.second);
				if(entidadMap.size()>0){
					if(this->clientName == entidadMap.at("owner")){
						this->idEntitySelected=atoi(entidadMap.at("id").c_str());
					}
					this->juegoVista->getMenuVista()->setSelectedEntityDescription(entidadMap);
				}else{
					this->juegoVista->getMenuVista()->deselectedEntity();
					this->idEntitySelected=0;
				}
			}
		}

		if( event->type == SDL_QUIT){
			this->juegoVista->getMenuVista()->deselectedEntity();
			this->salirDelJuego = true;
			Message* message = new Message();
			msg_game body;
			body.set_id(0);
			body.set_nombre(userName);
			body.set_tipo("exit");
			message->setContent(body);
			return message;
		}
	}
	return NULL;
}

JuegoVista* GameController::getJuegoVista(){
	return this->juegoVista;
}

void GameController::setGameRunning(){
	this->gameRunning=true;
}

void GameController::updateGame(){
	map<int,EntidadDinamicaVista*>* misEntidades = this->juegoVista->getMyEntities();
	for(map<int,EntidadDinamicaVista*>::iterator it = misEntidades->begin(); it !=misEntidades->end(); ++it){
		updatePosition((*it).second->getId());
	}

	map<int,EntidadDinamicaVista*>* entidades = this->juegoVista->getPersonajes();
	for(map<int,EntidadDinamicaVista*>::iterator it = entidades->begin(); it !=entidades->end(); ++it){
		updatePosition((*it).second->getId());
	}

	pair<int,int> offset = this->getOffset(this->juegoVista->getOffset()->first,this->juegoVista->getOffset()->second);
	juegoVista->actualizarOffset(offset.first,offset.second);
}

int GameController::getRunCycles(){
	return this->runCycles;
}

int GameController::getMaxFramesPerSecond(){
	return this->maxFramesPerSecond;
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

pair<int,int> GameController::moveCharacter(EntidadDinamicaVista* entidad){
	pair<int,int>* offset = this->juegoVista->getOffset();
	pair<int,int> cartesianPosition = this->utils->convertToCartesian( this->posMouseX-offset->first, this->posMouseY-offset->second);

	//las coordenadas cartesianas siempre tienen que quedar dentro del mapa
	if( cartesianPosition.first < 0 ){
		cartesianPosition.first = 0;
	}else if( cartesianPosition.first >= gameSettings->getMapWidth()){
		cartesianPosition.first = gameSettings->getMapWidth() - 1 ;
	}
	if( cartesianPosition.second < 0){
		cartesianPosition.second = 0;
	}else if( cartesianPosition.second >= gameSettings->getMapHeight()){
		cartesianPosition.second = gameSettings->getMapHeight() - 1;
	}

	return cartesianPosition;
}

void GameController::updatePosition(int id){
	EntidadDinamicaVista* entity = this->juegoVista->getEntityById(id);
	if( !(entity->getCamino()->empty()) && !(entity->isWalking())){
		pair<int,int> nuevaPos = entity->getCamino()->front();
		entity->getCamino()->pop_front();

		entity->setPosition(nuevaPos.first,nuevaPos.second);
		pair<int,int> destinoIsometrico = this->utils->GetInstance()->getIsometricPosition(nuevaPos.first,nuevaPos.second);
		entity->setScreenPosition(destinoIsometrico.first,destinoIsometrico.second);
	}
}

void GameController::addTileToCharacter(int id,int x,int y){
	EntidadDinamicaVista* entity = this->juegoVista->getEntityById(id);
	entity->addTileToPath(x,y);
}

void GameController::resetPath(int id){
	EntidadDinamicaVista* entity = this->juegoVista->getEntityById(id);
	entity->getCamino()->clear();
}

void GameController::delay(){
	this->runCycles++;
	if(this->gameRunning){
		SDL_Delay(50); // para que sean 50 frames x segundos
	}else{
		SDL_Delay(1000); // espero 1 segundo porque aun no esta en juego
	}
}

bool GameController::gameIsRunning(){
	return this->gameRunning;
}

void GameController::setClientName(string name){
	this->clientName = name;
}

GameController::~GameController() {
	//delete(this->juegoVista);
	this->juegoVista=NULL;
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

