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

	this->position.first = x;
	this->position.second = y;

	//no importa el destino inicial porque no esta caminando
	this->destinoX = x;
	this->destinoY = y;

	this->velocidad = vel;
	this->velX = 0;
	this->velY = 0;

}

pair<float,float>* EntidadDinamica::getPosition(){
	return &this->position;
}

float EntidadDinamica::distanciaEnX(float x){

	float res;
	if(position.first > x) res = position.first - x;
	else res = x - position.first;

	return res;
}

float EntidadDinamica::distanciaEnY(float y){

	float res;
	if(position.second > y) res = position.second - y;
	else res = y - position.second;

	return res;
}

float EntidadDinamica::distanciaA(float x, float y){

	float distY = (position.second - y);
	float distX = (position.first - x);

	return sqrt((distX * distX) +  (distY * distY));
}

Direccion EntidadDinamica::getDireccionVertical(){

	//para que la direccion sea norte/sur el seno del angulo tiene que ser mayor a 0.38
	// equivale a un angulo de 22,5 grados o mas

	Direccion dVertical = Sindireccion;
	if(caminando && (velY / velocidad > 0.38 )){
		if(position.second > destinoY) dVertical = Norte;
		else dVertical = Sur;
	}

	return dVertical;
}

Direccion EntidadDinamica::getDireccionHorizontal(){

	Direccion dHorizontal = Sindireccion;
	if(caminando && (velX / velocidad > 0.38)){
		if(position.first > destinoX) dHorizontal = Oeste;
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

void EntidadDinamica::setPosition(int x,int y){
	this->position.first = x;
	this->position.second = y;
}

void EntidadDinamica::setScreenPosition(float x,float y){

	this->destinoX = x;
	this->destinoY = y;

	//calcula la velocidad en cada eje para ir al destino
	float distanciaDest = distanciaA(x,y);
	if(distanciaDest > 0) caminando = true;

	float seno = distanciaEnY(y) / distanciaDest;
	float coseno = distanciaEnX(x) / distanciaDest;

	this->velX = velocidad * coseno;
	this->velY = velocidad * seno;
}

void EntidadDinamica::trasladarse(){

	if(caminando){

		if(position.first > destinoX) position.first -= velX;
		if(position.first < destinoX) position.first += velX;

		if(position.second > destinoY) position.second -= velY;
		if(position.second < destinoY) position.second += velY;
	}

	if(distanciaEnX(destinoX) <= velX){

		position.first = destinoX;
		caminando = false;
	}

	if(distanciaEnY(destinoY) <= velY){

		position.second = destinoY;
		caminando = false;
	}

}

EntidadDinamica::~EntidadDinamica() {
	// TODO Auto-generated destructor stub
}

