/*
 * Juego.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/Juego.h"

using namespace std;

Juego::Juego() {
	gameSettings = GameSettings::GetInstance();
	this->juegoFinalizado = false;
	this->mapa = new Mapa();
	this->currentAge = gameSettings->getAgeOfEmpires();
}

void Juego::agregarProtagonista(int owner){
	//TODO revisar que le ponemos en tipo
	EntidadDinamica *protagonista = new EntidadDinamica(gameSettings->getTipoProtagonista(),
				gameSettings->getVelocidadPersonaje(),
				gameSettings->getPosXProtagonista(),
				gameSettings->getPosYProtagonista(),
				gameSettings->getProtagonistaPixelDimension(),
				gameSettings->getProtagonistaPixelDimension(),
				gameSettings->getProtagonistaFPS());

		protagonista->setFramesInLineFile(gameSettings->getProtagonistaFramesInFile());
		protagonista->setDelay(gameSettings->getProtagonistaDelay());
		protagonista->setOwner(owner);
		//TODO: esto creo que no deberia ser asi. Deberia setear solo posiciones en tiles y  las posiciones de pantalla deberia estar en la vista nada mas
		pair<float,float> isometricas = this->getIsometricPosition(protagonista);
		protagonista->setInitialScreenPosition(isometricas.first + gameSettings->getTileSize() ,isometricas.second);
		this->protagonistas.push_back(protagonista);
}

Mapa* Juego::getMap(){
	return this->mapa;
}

list<EntidadDinamica*> Juego::getProtagonistas(){
	return this->protagonistas;
}

void Juego::actualizarProtagonistas(){
	for(list<EntidadDinamica*>::iterator it=this->protagonistas.begin(); it!=this->protagonistas.end(); ++it){
		(*it)->trasladarse();
	}
}

string Juego::getCurrentAge(){
	return this->currentAge;
}


void Juego::setDestinoProtagonista(int x,int y, int screenPosX, int screenPosY){
	//TODO: aca deberiamos setear las coordenadas de panatalla? eso no deberia solo hacerse en la vista?
	/*
	//Actualiza las coordenadas cartesianas del protagonista
	this->protagonista->setPosition(x,y);
	//Actualizo las coordenadas de pantalla del protagonista
	this->protagonista->setScreenPosition(screenPosX - this->offset.first,screenPosY - this->offset.second);
	*/
}

void Juego::terminarJuego(){
	this->juegoFinalizado = true;
}
bool Juego::getStatusPartida(){
	return this->juegoFinalizado;
}

pair<int,int> Juego::getIsometricPosition(EntidadPartida* entidad){
	//TODO: esto no deberia estar solo en la vista?

	pair<int,int> isometricPosition;
	//hacemos coincidir el vertice superior izquierdo de la entidad con el tile
	isometricPosition.first = (entidad->getPosition()->first - entidad->getPosition()->second) * gameSettings->getTileSize() + gameSettings->getScreenWidth() / 2;
	isometricPosition.second = (entidad->getPosition()->first + entidad->getPosition()->second) * gameSettings->getTileSize() / 2  ;

	//ahora hay que centrar la entidad con el tile
	isometricPosition.first = isometricPosition.first - (entidad->getWidth() - 1)  *  gameSettings->getTileSize();
	isometricPosition.second = isometricPosition.second - (entidad->getLength() - 1) *  gameSettings->getTileSize() / 2;
	return isometricPosition;
}

Juego::~Juego() {
	for(list<EntidadDinamica*>::iterator it=this->protagonistas.begin(); it!=this->protagonistas.end(); ++it){
			delete(*it);
	}
	delete(this->mapa);
	this->mapa = NULL;
	this->gameSettings=NULL;
}
