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
	this->reiniciar = false;
	this->event = new SDL_Event();
	this->posMouseX = 0;
	this->posMouseY = 0;
	this->runCycles = 0;
	this->maxFramesPerSecond = 50; // maxima cantidad de frames del juego principal
}

Message* GameController::getMessageFromEvent(string userId){

	while(SDL_PollEvent(event)){

		if( event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT){
			SDL_GetMouseState(&posMouseX,&posMouseY);
			if ( posMouseY >= gameSettings->getScreenHeight()-gameSettings->getAlturaMenuInferior() ){
				// aca iria algo en caso de que el menu sea interactivo
			} else {
			int id;
			pair<int,int> cartesianPosition;
			map<int,EntidadDinamicaVista*>* misPersonajes = this->juegoVista->getMyEntities();

			//TODO identidicar cual es la entidad del cliente que se desea mover, hoy esto anda porque tenemos un unico
			//personaje
			for(map<int,EntidadDinamicaVista*>::iterator it = misPersonajes->begin(); it != misPersonajes->end(); ++it){
				id = (*it).first;
				cartesianPosition = this->moveCharacter((*it).second);
				cout << "La nueva posicion es: "<<cartesianPosition.first<<";"<<cartesianPosition.second<<endl;
			}

			//creamos el mensaje que vamos a enviar al server
			Message* message = new Message();
			msg_game body;
			body.set_id(id);
			body.set_tipo("update");
			body.set_x(cartesianPosition.first);
			body.set_y(cartesianPosition.second);
			message->setContent(body);
			return message;
			}
		}

		if( event->type == SDL_QUIT){
			this->salirDelJuego = true;
			Message* message = new Message();
			msg_game body;
			body.set_id(0);
			body.set_nombre(userId);
			body.set_tipo("exit");
			message->setContent(body);
			return message;
		}
		if( event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_r){
			this->reiniciar = true;
			/*TODO esto parece que no va mas asique lo podriamos ir sacando
			 **/
			return NULL;
		}
	}
	return NULL;
}

JuegoVista* GameController::getJuegoVista(){
	return this->juegoVista;
}

void GameController::actualizarJuego(){
	//TODO: esto deberia actualizar el juegoVista?
	//juegoVista->actualizarProtagonista();
	pair<int,int> offset = this->getOffset(this->juegoVista->getOffset()->first,this->juegoVista->getOffset()->second);
	juegoVista->actualizarOffset(offset.first,offset.second);
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
	//cout << "1.1: "<<gameSettings->getMargenInferiorUno()<< "1.2: "<<gameSettings->getMargenInferiorDos()<< " 2.1: " <<gameSettings->getMargenSuperiorUno() << " 2.2: " << gameSettings->getMargenSuperiorDos()<<endl;
	pair<int,int> curretOffset;
	curretOffset.first = offSetX;
	curretOffset.second = offSetY;
	return curretOffset;
}

pair<int,int> GameController::moveCharacter(EntidadDinamicaVista* entidad){
	pair<int,int>* offset = this->juegoVista->getOffset();
	pair<int,int> cartesianPosition = this->utils->convertToCartesian( this->posMouseX-offset->first, this->posMouseY-offset->second);
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
	pair<int,int> isometricPosition;
	if(correctPosition){
		isometricPosition = this->utils->getIsometricPosition(cartesianPosition.first,cartesianPosition.second);
		isometricPosition.first = isometricPosition.first + offset->first;
		isometricPosition.second= isometricPosition.second + offset->second;
	}else{
		isometricPosition.first = posMouseX;
		isometricPosition.second= posMouseY;
	}

	entidad->setScreenPosition(isometricPosition);
	//una vez convertida a cartesiana la posicion le decimos al modelo que se actualize
	//TODO: Aca deberia actualizar la posicion del protagonsita?
	//juego->setDestinoProtagonista(cartesianPosition.first,cartesianPosition.second,posMouseX,posMouseY);
	return cartesianPosition;
}

void GameController::updatePostion(int id,int x,int y){

	map<int,EntidadDinamicaVista*>* myEntities = this->juegoVista->getMyEntities();
	EntidadDinamicaVista* entity = myEntities->at(id);

	stringstream ss;
	ss << "La posicion vieja de: "<< id <<" es "<<entity->getPosition()->first<<" "<<entity->getPosition()->first;
	Logger::get()->get()->logDebug("GameController","updatePostion",ss.str());

	entity->setPosition(x,y);

	//esto no se si va aca
	/*
	//paso x y a isometricas
	pair<float,float> isometricPos = this->utils->getIsometricPosition(x,y);
	pair<int,int>* offset = this->juegoVista->getOffset();
	//le sumo el offset a la posicion isometrica
	isometricPos.first = isometricPos.first + offset->first;
	isometricPos.second = isometricPos.second + offset->second;
	entity->setScreenPosition(isometricPos);
	*/

	ss << "La posicion actualizada de: "<< id <<" es "<<x<<" "<<y;
	Logger::get()->get()->logDebug("GameController","updatePostion",ss.str());

}

void GameController::delay(){
	this->runCycles++;

	SDL_Delay(50); // para que sean 50 frames x segundos
	//}
}
GameController::~GameController() {
	//TODO: ver si no es necesario ejecutar el destructor de juego Vista
	//No ejecuto el destructor de juego porque lo hace el juegoVista
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

