/*
 * Juego.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "Juego.h"

using namespace std;

Juego::Juego() {
	// TODO Auto-generated constructor stub
	this->juegoFinalizado = false;
	this->mapa = new Mapa();
	this->currentAge = DefaultSettings::getAgeOfEmpires();
	this->protagonista = new EntidadDinamica(12,10,4,350,300);
}

Mapa* Juego::getMap(){
	return this->mapa;
}

EntidadDinamica* Juego::getProtagonista(){
	return this->protagonista;
}

void Juego::actualizarProtagonista(){
	protagonista->trasladarse();
}

string Juego::getCurrentAge(){
	return this->currentAge;
}

void Juego::setDestinoProtagonista(int x,int y, int screenPosX, int screenPosY){
	//Actualiza las coordenadas cartesianas del protagonista
	this->protagonista->setPosition(x,y);
	this->protagonista->setScreenPosition(screenPosX,screenPosY);
}

void Juego::terminarJuego(){
	this->juegoFinalizado = true;
}
bool Juego::getStatusPartida(){
	return this->juegoFinalizado;
}

Juego::~Juego() {
	// TODO Auto-generated destructor stub
}
