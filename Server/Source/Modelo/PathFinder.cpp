/*
 * PathFinder.cpp
 *
 *  Created on: Oct 2, 2015
 *      Author: juan
 */

#include "../../Headers/Modelo/PathFinder.h"

using namespace std;

PathFinder::PathFinder(int x,int y,int dX,int dY) {

	this->posX = x;
	this->posY = y;

	this->destinoX = dX;
	this->destinoY = dY;

	this->candidatos = new list<candidato>();

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

	int minimo = this->inicio.dist;
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

void PathFinder::buscarCamino(){
	this->setInicio();
	candidato actual = this->inicio;
	this->candidatos->push_front(inicio);

	int minimo = actual.dist; //me parece que no sirve
	bool encontrado = false;

	while( !encontrado ){

		candidato cand1 = getAdyacente(actual.posX,actual.posY,actual.posX + 1,actual.posY);
		if( ! candidatoExiste(cand1) ) candidatos->push_front(cand1);
		candidato cand2 = getAdyacente(actual.posX,actual.posY,actual.posX + 1,actual.posY - 1);
		if( ! candidatoExiste(cand2) ) candidatos->push_front(cand2);
		candidato cand3 = getAdyacente(actual.posX,actual.posY,actual.posX,actual.posY - 1);
		if( ! candidatoExiste(cand3) ) candidatos->push_front(cand3);
		candidato cand4 = getAdyacente(actual.posX,actual.posY,actual.posX - 1,actual.posY - 1);
		if( ! candidatoExiste(cand4) ) candidatos->push_front(cand4);
		candidato cand5 = getAdyacente(actual.posX,actual.posY,actual.posX - 1,actual.posY);
		if( ! candidatoExiste(cand5) ) candidatos->push_front(cand5);
		candidato cand6 = getAdyacente(actual.posX,actual.posY,actual.posX - 1,actual.posY + 1);
		if( ! candidatoExiste(cand6) ) candidatos->push_front(cand6);
		candidato cand7 = getAdyacente(actual.posX,actual.posY,actual.posX,actual.posY + 1);
		if( ! candidatoExiste(cand7) ) candidatos->push_front(cand7);
		candidato cand8 = getAdyacente(actual.posX,actual.posY,actual.posX + 1,actual.posY + 1);
		if( ! candidatoExiste(cand8) ) candidatos->push_front(cand8);

		actual = getMinimoNoRecorrido();
		if(actual.dist == 0) encontrado = true;

	}

	cout<<"quiero ir de "<<this->inicio.posX<<","<<this->inicio.posY;
	cout<<" a "<<this->destinoX<<","<<this->destinoY<<endl;
	cout<<"el camino es: "<<endl;
	cout<<actual.posX<<","<<actual.posY<<endl;
	while(actual.origenX != -1){
		cout<<actual.posX<<","<<actual.posY<<endl;
		actual = getCandidato(actual.origenX,actual.origenY);
	}

}

PathFinder::~PathFinder() {
	// TODO Auto-generated destructor stub
}

