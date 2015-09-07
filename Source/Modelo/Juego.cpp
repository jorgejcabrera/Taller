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
	this->mapa->show();
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
