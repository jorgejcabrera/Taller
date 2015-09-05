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
}

void Juego::setTilesPosition(){
    int yTiles = defaultSettings->getScreenHeight() /  defaultSettings->getTileSize();
    int aux;

    for (int i = 0; i < yTiles; i++){
    	aux = i;
    	this->setTilesTopPosition(++aux);
    	if ( i < yTiles - 1 ){
    		aux = i;
    		this->setTilesLowerPosition(++aux);
    	}
    }
}

void Juego::setTilesLowerPosition(int cant){
	int x = (defaultSettings->getScreenWidth() / 2) - (cant - 1) * (defaultSettings->getTileSize() / 2 + 20);
	int y = defaultSettings->getScreenHeight() - (cant - 1) *  defaultSettings->getTileSize() / 2 -  defaultSettings->getTileSize();
	//barrido horizontal de los tiles
	for(int i=0;i<cant;i++){
		//renderTexture(image, ren, x, y,  defaultSettings->getTileSize() * 2, defaultSettings->getTileSize());
		x +=  defaultSettings->getTileSize() * 2;
	}
}

void Juego::setTilesTopPosition(int cant){
	int x = (defaultSettings->getScreenWidth() / 2) - (cant - 1) * defaultSettings->getTileSize();
	int y = (cant - 1) *  defaultSettings->getTileSize() / 2;
	//barrido horizontal de los tiles
	for(int i=0;i<cant;i++){
		//renderTexture(image, ren, x, y,  defaultSettings->getTileSize() * 2, defaultSettings->getTileSize());
		x +=  defaultSettings->getTileSize() * 2;
	}
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
