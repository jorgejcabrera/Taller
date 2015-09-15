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
	this->protagonista = new EntidadDinamica("soldado",10,300,300,50,50,6);
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

void Juego::setDestinoProtagonista(int x,int y){
	protagonista->setDestino(x,y);
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
