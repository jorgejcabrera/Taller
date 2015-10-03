/*
 * PathFinder.cpp
 *
 *  Created on: Oct 2, 2015
 *      Author: juan
 */

#include "PathFinder.h"

PathFinder::PathFinder(int x,int y,int dX,int dY) {

	this->posX = x;
	this->posY = y;

	this->destinoX = dX;
	this->destinoY = dY;
}

int PathFinder::dManhattan(int x,int y){

	int dist = 0;
	if(this->destinoX > x) dist += (destinoX - x);
	else dist += (x - destinoX);

	if(this->destinoY > y) dist += (destinoY - y);
	else dist += (y - destinoY);

	return dist;
}

candidato PathFinder::getAdyacente(int oX,int oY,int x,int y){

	candidato ady;
	ady.origenX = oX;
	ady.origenY = oY;
	ady.dist = this->dManhattan(x,y);
	ady.posX = x;
	ady.posY = y;
	ady.recorrido = false;

	return ady;
}

void PathFinder::setInicio(){

	this->inicio.origenX = this->posX;
	this->inicio.origenY = this->posY;
	this->inicio.dist = this->dManhattan(posX,posY);
	this->inicio.origenX = -1;
	this->inicio.origenY = -1;
	this->inicio.recorrido = true;

}

void PathFinder::buscarCamino(){
	this->setInicio();
	candidato actual = this->inicio;

	int minimo = actual.dist;
	bool encontrado = false;

}

PathFinder::~PathFinder() {
	// TODO Auto-generated destructor stub
}

