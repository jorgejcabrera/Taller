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

EntidadDinamica::EntidadDinamica(int vel,float x,float y) {

	this->caminando = false;

	this->posX = x;
	this->posY = y;

	//no importa el destino inicial porque no esta caminando
	this->destinoX = x;
	this->destinoY = y;

	this->velocidad = vel;
	this->velX = 0;
	this->velY = 0;

}

float EntidadDinamica::getX(){
	return this->posX;
}

float EntidadDinamica::getY(){
	return this->posY;
}

float EntidadDinamica::distanciaEnX(float x){

	float res;
	if(posX > x) res = posX - x;
	else res = x - posX;

	return res;
}

float EntidadDinamica::distanciaEnY(float y){

	float res;
	if(posY > y) res = posY - y;
	else res = y - posY;

	return res;
}

float EntidadDinamica::distanciaA(float x, float y){

	float distY = (posY - y);
	float distX = (posX - x);

	return sqrt((distX * distX) +  (distY * distY));
}

Direccion EntidadDinamica::getDireccionVertical(){

	//para que la direccion sea norte/sur el seno del angulo tiene que ser mayor a 0.38
	// equivale a un angulo de 22,5 grados o mas

	Direccion dVertical = Sindireccion;
	if(caminando && (velY / velocidad > 0.38 )){
		if(posY > destinoY) dVertical = Norte;
		else dVertical = Sur;
	}

	return dVertical;
}

Direccion EntidadDinamica::getDireccionHorizontal(){

	Direccion dHorizontal = Sindireccion;
	if(caminando && (velX / velocidad > 0.38)){
		if(posX > destinoX) dHorizontal = Oeste;
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

void EntidadDinamica::setDestino(float x,float y){

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

		if(posX > destinoX) posX -= velX;
		if(posX < destinoX) posX += velX;

		if(posY > destinoY) posY -= velY;
		if(posY < destinoY) posY += velY;
	}

	if(distanciaEnX(destinoX) <= velX){

		posX = destinoX;
		caminando = false;
	}

	if(distanciaEnY(destinoY) <= velY){

		posY = destinoY;
		caminando = false;
	}

}

EntidadDinamica::~EntidadDinamica() {
	// TODO Auto-generated destructor stub
}

