/*
 * EntidadDinamica.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "EntidadDinamica.h"

EntidadDinamica::EntidadDinamica(){
	//esto no sirve, hay que borrarlo
}

EntidadDinamica::EntidadDinamica(int vel,int x,int y) {

	this->caminando = false;
	//son las coordenadas cartesianas de donde se va a posicionar el chabon
	this->position.first = x;
	this->position.first = x = y;
	this->velocidad = vel;
	this->width = 50;
	this->length = 50;
}

EntidadDinamica::EntidadDinamica(string typeDinamicEntity, int vel,float x,float y, float widthPixel, float lengthPixels, int fps){
	this->caminando = false;
	this->position.first = x;
	this->position.second = y;
	this->velocidad = vel;
	this->vecVelocity.first = 0;
	this->vecVelocity.second = 0;

	//el ancho y el largo es siempre el del tamaño del tile
	this->width = 1;
	this->length = 1;
	this->widthPixel = widthPixel;
	this->lengthPixel = lengthPixels;
	this->framesPerSecond = fps;
	this->setPathImage(DefaultSettings::imagePathPersonajesByType(typeDinamicEntity));
}

SDL_Rect EntidadDinamica::getPositionOfSprite(){
	Uint32 sprite = 0;
	if(this->caminando){
		Uint32 ticks = SDL_GetTicks();
		sprite = (ticks / 100) % this->framesPerSecond;
	}
	int lineaSprite = this->getLineSprite(this->getDireccion());
	SDL_Rect srcrect = { sprite * this->widthPixel, this->lengthPixel*lineaSprite, this->widthPixel, this->lengthPixel };
	return srcrect;
}

void EntidadDinamica::setInitialScreenPosition(float x,float y){
	// no borrar por favor
	this->screenPosition.first = x;
	this->screenPosition.second = y;
}

pair<float,float>* EntidadDinamica::getScreenPosition(){
	return &this->screenPosition;
}

pair<int,int>* EntidadDinamica::getPosition(){
	return &this->position;
}

float EntidadDinamica::distanciaEnX(float x){
	float res;
	if(screenPosition.first > x) res = screenPosition.first - x;
	else res = x - screenPosition.first;
	return res;
}

float EntidadDinamica::distanciaEnY(float y){
	float res;
	if(screenPosition.second > y) res = screenPosition.second - y;
	else res = y - screenPosition.second;
	return res;
}

float EntidadDinamica::distanciaA(float x, float y){
	float distY = (screenPosition.second - y);
	float distX = (screenPosition.first - x);
	return sqrt((distX * distX) +  (distY * distY));
}

Direccion EntidadDinamica::getDireccionVertical(){
	//para que la direccion sea norte/sur el seno del angulo tiene que ser mayor a 0.38
	// equivale a un angulo de 22,5 grados o mas

	Direccion dVertical = Sindireccion;
	if(caminando && (vecVelocity.second / velocidad > 0.38 )){
		if(screenPosition.second > destinoY) dVertical = Norte;
		else dVertical = Sur;
	}
	return dVertical;
}

Direccion EntidadDinamica::getDireccionHorizontal(){
	Direccion dHorizontal = Sindireccion;
	if(caminando && (vecVelocity.first / velocidad > 0.38)){
		if(screenPosition.first > destinoX) dHorizontal = Oeste;
		else dHorizontal = Este;
	}
	return dHorizontal;
}

Direccion EntidadDinamica::getDireccion(){
	Direccion dir = Sindireccion;
	Direccion dVertical = getDireccionVertical();
	Direccion dHorizontal = getDireccionHorizontal();

	switch(dVertical){
	case Sindireccion: dir = dHorizontal; break;
	case Norte: switch(dHorizontal){
				case Sindireccion: dir = Norte;break;
				case Este: dir = Noreste;break;
				case Oeste: dir = Noroeste;
				} break;
	case Sur: switch(dHorizontal){
			  case Sindireccion: dir = Sur;break;
			  case Este: dir = Sureste;break;
			  case Oeste: dir = Suroeste;break;
			  }
	}
	return dir;
}

int EntidadDinamica::getLineSprite(Direccion dir){
	switch(dir){
	case Norte: return 1; break;
	case Noreste: return 2; break;
	case Este: return 0; break;
	case Sureste: return 5; break;
	case Sur: return 4; break;
	case Suroeste: return 5; break;
	case Oeste: return 7; break;
	case Noroeste: return 3; break;
	case Sindireccion: return 0; break;
	}
}

void EntidadDinamica::setScreenPosition(float x,float y){
	this->destinoX = x;
	this->destinoY = y;

	//calcula la velocidad en cada eje para ir al destino
	float distanciaDest = distanciaA(x,y);
	if(distanciaDest > 0) caminando = true;

	float seno = distanciaEnY(y) / distanciaDest;
	float coseno = distanciaEnX(x) / distanciaDest;

	this->vecVelocity.first = velocidad * coseno;
	this->vecVelocity.second = velocidad * seno;
}

void EntidadDinamica::trasladarse(){

	if(distanciaEnX(destinoX) <= vecVelocity.first){

			screenPosition.first = destinoX;
			caminando = false;
		}

	if(distanciaEnY(destinoY) <= vecVelocity.second){

			screenPosition.second = destinoY;
			caminando = false;
		}

	if(caminando){

		if(screenPosition.first > destinoX) screenPosition.first -= vecVelocity.first;
		if(screenPosition.first < destinoX) screenPosition.first += vecVelocity.first;

		if(screenPosition.second > destinoY) screenPosition.second -= vecVelocity.second;
		if(screenPosition.second < destinoY) screenPosition.second += vecVelocity.second;
	}
}


EntidadDinamica::~EntidadDinamica() {
}

