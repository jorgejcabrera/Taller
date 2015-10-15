/*
 * PathFinder.cpp
 *
 *  Created on: Oct 2, 2015
 *      Author: juan
 */

#include "../../Headers/Modelo/PathFinder.h"

PathFinder::PathFinder(int x,int y,int dX,int dY,Mapa* unMap) {

	gameSettings = GameSettings::GetInstance();
	this->map = unMap;

	this->posX = x;
	this->posY = y;
	this->destinoX = dX;
	this->destinoY = dY;
	this->candidatos = new list<candidato>();

	if( ! positionAvailable(destinoX,destinoY)){
		pair<int,int> nuevoDestino = getClosestAvailable(destinoX,destinoY);
		this->destinoX = nuevoDestino.first;
		this->destinoY = nuevoDestino.second;
	}

}

int PathFinder::dManhattan(int x,int y){

	int dist = 0;

	if(this->destinoX > x) dist += (destinoX - x);
	else dist += (x - destinoX);

	if(this->destinoY > y) dist += (destinoY - y);
	else dist += (y - destinoY);

	//pongo distancia muy grande si esta afuera del mapa
	if(x < 0 || y < 0) dist = 5000;
	if(x > (gameSettings->MAP_WIDTH -1) || y > (gameSettings->MAP_HEIGHT -1)) dist = 5000;

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

pair<int,int> PathFinder::getClosestAvailable(int x,int y){

	candidato cand;
	cand.posX = this->destinoX;
	cand.posY = this->destinoY;
	int i = 1;
	while(cand.posX == this->destinoX && cand.posY == this->destinoY){
		if(positionAvailable(this->destinoX - i,this->destinoY)) cand = getAdyacente(-1,-1,destinoX - i,destinoY);
		if(positionAvailable(this->destinoX,this->destinoY - i)) cand = getAdyacente(-1,-1,destinoX,destinoY - i);
		if(positionAvailable(this->destinoX,this->destinoY + 1)) cand = getAdyacente(-1,-1,destinoX,destinoY + 1);
		if(positionAvailable(this->destinoX + 1,this->destinoY)) cand = getAdyacente(-1,-1,destinoX + 1,destinoY);
		i++;
	}

	pair<int,int> nDest;
	nDest.first = cand.posX;
	nDest.second = cand.posY;
	return nDest;
}

void PathFinder::setInicio(){

	this->inicio.posX = this->posX;
	this->inicio.posY = this->posY;
	this->inicio.dist = this->dManhattan(posX,posY);
	this->inicio.origenX = -1;
	this->inicio.origenY = -1;
	this->inicio.recorrido = true;

}

bool PathFinder::candidatoExiste(candidato can){

	bool existe = false;

	for (std::list<candidato>::iterator it=this->candidatos->begin(); it != this->candidatos->end(); ++it)
	    if(can.posX == (*it).posX && can.posY == (*it).posY) existe = true;

	return existe;
}

candidato PathFinder::getMinimoNoRecorrido(){

	int minimo = (this->gameSettings->MAP_HEIGHT * 3);
	candidato candidatoMinimo;
	for (std::list<candidato>::iterator it=this->candidatos->begin(); it != this->candidatos->end(); ++it)
		if( (*it).dist < minimo &&  ! (*it).recorrido){
			candidatoMinimo = (*it);
			minimo = candidatoMinimo.dist;
		}

	return candidatoMinimo;
}

candidato PathFinder::getCandidato(int x,int y){
	candidato cand;
	for (std::list<candidato>::iterator it=this->candidatos->begin(); it != this->candidatos->end(); ++it)
			if( (*it).posX == x &&  (*it).posY == y) cand = (*it);

	return cand;
}

void PathFinder::getCandidatosAdyacentes(candidato actual){

	int oX = actual.posX;
	int oY = actual.posY;

	int x = oX + 1;
	int y = oY;

	candidato cand1 = getAdyacente(oX,oY,x,y);
	if( ! candidatoExiste(cand1) && positionAvailable(x,y) ) candidatos->push_front(cand1);

	y = oY - 1;
	candidato cand2 = getAdyacente(oX,oY,x,y);
	if( ! candidatoExiste(cand2) && positionAvailable(x,y)) candidatos->push_front(cand2);

	x = oX;
	candidato cand3 = getAdyacente(oX,oY,x,y);
	if( ! candidatoExiste(cand3) && positionAvailable(x,y) ) candidatos->push_front(cand3);

	x = oX - 1;
	candidato cand4 = getAdyacente(oX,oY,x,y);
	if( ! candidatoExiste(cand4) && positionAvailable(x,y)) candidatos->push_front(cand4);

	y = oY;
	candidato cand5 = getAdyacente(oX,oY,x,y);
	if( ! candidatoExiste(cand5) && positionAvailable(x,y) ) candidatos->push_front(cand5);

	y = oY + 1;
	candidato cand6 = getAdyacente(oX,oY,x,y);
	if( ! candidatoExiste(cand6) && positionAvailable(x,y) ) candidatos->push_front(cand6);

	x = oX;
	candidato cand7 = getAdyacente(oX,oY,x,y);
	if( ! candidatoExiste(cand7) && positionAvailable(x,y)) candidatos->push_front(cand7);

	x = oX + 1;
	candidato cand8 = getAdyacente(oX,oY,x,y);
	if( ! candidatoExiste(cand8) && positionAvailable(x,y)) candidatos->push_front(cand8);
}

bool PathFinder::positionAvailable(int x,int y){

	if(x < 0 || y < 0) return false;
	if(x > gameSettings->MAP_HEIGHT - 1 || y > gameSettings->MAP_WIDTH -1) return false;

	return this->map->getTileAt(x,y)->isAvailable();
}

list<pair<int,int> >* PathFinder::buscarCamino(){

	pair<int,int> unPar;
	list<pair<int,int> >* camino = new list<pair<int,int> >();
	camino->clear();
	this->setInicio();

	if(inicio.posX == destinoX && inicio.posY == destinoY)
		return camino;

	candidato actual = this->inicio;
	this->candidatos->push_front(inicio);

	bool encontrado = false;

	while( !encontrado ){

		getCandidatosAdyacentes(actual);

		actual = getMinimoNoRecorrido();
		this->candidatos->remove(actual);
		actual.recorrido = true;
		this->candidatos->push_front(actual);
		if(actual.dist == 0) encontrado = true;
	}

	while(actual.origenX != -1){
		unPar.first = actual.posX;
		unPar.second = actual.posY;
		camino->push_front(unPar);
		actual = getCandidato(actual.origenX,actual.origenY);
	}

	return camino;

}

PathFinder::~PathFinder() {
	delete candidatos;
}

