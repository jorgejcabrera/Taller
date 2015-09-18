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
	this->protagonista = new EntidadDinamica("soldado",10,4,4,50,50,15);

	pair<float,float> isometricas = this->getIsometricPosition(protagonista);
	protagonista->setInitialScreenPosition(isometricas.first + DefaultSettings::getTileSize() ,isometricas.second);
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
	//Actualizo las coordenadas de pantalla del protagonista
	this->protagonista->setScreenPosition(screenPosX,screenPosY);
}

void Juego::terminarJuego(){
	this->juegoFinalizado = true;
}
bool Juego::getStatusPartida(){
	return this->juegoFinalizado;
}

pair<int,int> Juego::getIsometricPosition(EntidadPartida* entidad){
	pair<int,int> isometricPosition;
	//hacemos coincidir el vertice superior izquierdo de la entidad con el tile
	isometricPosition.first = (entidad->getPosition()->first - entidad->getPosition()->second) * DefaultSettings::getTileSize() + DefaultSettings::getScreenWidth() / 2;
	isometricPosition.second = (entidad->getPosition()->first + entidad->getPosition()->second) * DefaultSettings::getTileSize() / 2  ;

	//ahora hay que centrar la entidad con el tile
	isometricPosition.first = isometricPosition.first - (entidad->getWidth() - 1)  *  DefaultSettings::getTileSize();
	isometricPosition.second = isometricPosition.second - (entidad->getLength() - 1) *  DefaultSettings::getTileSize() / 2;
	return isometricPosition;
}

Juego::~Juego() {
	// TODO Auto-generated destructor stub
}
