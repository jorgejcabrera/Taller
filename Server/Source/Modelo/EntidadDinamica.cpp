/*
 * EntidadDinamica.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/EntidadDinamica.h"

EntidadDinamica::EntidadDinamica(){
}

//TODO sacar los fps y el tamaño en pixel
EntidadDinamica::EntidadDinamica(string nameEntity,int vel,float x,float y, float widthPixel, float lengthPixels){
	this->caminando = false;
	this->notifiable = false;
	this->position.first = x;
	this->position.second = y;
	this->velocidad = vel;
	this->vecVelocity.first = 0;
	this->vecVelocity.second = 0;

	//el ancho y el largo es siempre el del tamaño del tile
	this->width = 1;
	this->length = 1;
	this->owner = "";
	this->name = nameEntity;
	this->camino = new list<pair<int,int> >();
	this->ciclos = (DefaultSettings::getTileSize() / vel) + 10;
	this->cicloActual = 0;
}

void EntidadDinamica::setOwner(string ownerId){
	this->owner = ownerId;
}

string EntidadDinamica::getOwner(){
	return this->owner;
}

void EntidadDinamica::setInitialScreenPosition(float x,float y){
	//TODO: esto no deberia estar en la VISTA nada mas?
	this->screenPosition.first = x;
	this->screenPosition.second = y;
}

void EntidadDinamica::nextPosition(){

	this->setNotifiable(false);
	if(! camino->empty()){
		if(cicloActual % ciclos == 0){
			pair<int,int> nextTile = camino->front();
			camino->pop_front();
			this->setNotifiable(true);

			this->setPosition(nextTile.first,nextTile.second);
		}
		cicloActual++;
	}
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

void EntidadDinamica::setNotifiable(bool noti){
	this->notifiable = noti;
}

bool EntidadDinamica::hasToNotify(){
	return notifiable;
}

float EntidadDinamica::distanciaA(float x, float y){
	float distY = (screenPosition.second - y);
	float distX = (screenPosition.first - x);
	return sqrt((distX * distX) +  (distY * distY));
}

list<pair<int,int> >* EntidadDinamica::getCamino(){
	return this->camino;
}

void EntidadDinamica::setCamino(list<pair<int,int> >* caminito){
	this->camino->clear();
	this->camino = caminito;
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
	case Suroeste: return 6; break;
	case Oeste: return 7; break;
	case Noroeste: return 3; break;
	case Sindireccion: return 0; break;
	}
}

void EntidadDinamica::setScreenPosition(float x,float y){
	/*TODO: esto no deberia estar en la VISTA nada mas?
	 * No deberia usar la posicion fisica en lugar de la de pantalla?
	*/
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
	//TODO porque se llama screenPosition? es de pantalla o es donde se va moviendo?
	/*if(distanciaEnX(destinoX) <= vecVelocity.first){
			screenPosition.first = destinoX;
			//Logger::get()->logDebug("a","b","mira como me ajusto X");
	}

	if(distanciaEnY(destinoY) <= vecVelocity.second){
			screenPosition.second = destinoY;
			//Logger::get()->logDebug("a","b","mira como me ajusto Y");
	}

	if(distanciaEnX(destinoX) <= vecVelocity.first && distanciaEnY(destinoY) <= vecVelocity.first)
		caminando = false;

	if(caminando){
		//Logger::get()->logDebug("a","b","mira como camino");
		if(screenPosition.first > destinoX)
			screenPosition.first -= vecVelocity.first;
		if(screenPosition.first < destinoX)
			screenPosition.first += vecVelocity.first;
		if(screenPosition.second > destinoY)
			screenPosition.second -= vecVelocity.second;
		if(screenPosition.second < destinoY)
			screenPosition.second += vecVelocity.second;
	}
	*/
}

void EntidadDinamica::destruir(){
	this->~EntidadDinamica();
}

EntidadDinamica::~EntidadDinamica() {
}

bool EntidadDinamica::isWalking(){
	return this->caminando;
}
