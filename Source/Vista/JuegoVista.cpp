/*
 * JuegoVista.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "JuegoVista.h"

void JuegoVista::drawIsometricMap(){
	gameSettings = GameSettings::GetInstance();
	int posX = 0;
	int posY = 0;
	int offsetX = this->juego->getOffset()->first;
	int offsetY = this->juego->getOffset()->second;
	for (map<pair<int,int>,Tile*>::iterator it = this->juego->getMap()->getTiles()->begin(); it != this->juego->getMap()->getTiles()->end();++it){
		Tile* tileActual = (*it).second;
		//transformo coordenadas cartesianas a isométricas
		posY = (tileActual->getPosX()+tileActual->getPosY()) * gameSettings->getTileSize() / 2 + offsetY;
		posX = (tileActual->getPosX()-tileActual->getPosY()) * gameSettings->getTileSize() + gameSettings->getScreenWidth() / 2 + offsetX;	//comienzo a dibujar de la mitad de la pantalla
		this->picassoHelper->renderObject(tileActual->getPathImage(),posX,posY,  gameSettings->getTileSize() * 2, gameSettings->getTileSize());
	}
}

void JuegoVista::drawStaticEntities(){
	pair<int,int> isometricPosition;
	int offSetX = this->juego->getOffset()->first;
	int offSetY = this->juego->getOffset()->second;

	for(map<pair<int,int>,EntidadPartida*>::iterator it=this->juego->getMap()->getEntities()->begin();it!=this->juego->getMap()->getEntities()->end();++it){
		EntidadPartida* entidad = (*it).second;
		isometricPosition = this->picassoHelper->getIsometricPosition(entidad);
		entidad->drawMe(isometricPosition,offSetX,offSetY);
	}
}

void JuegoVista::render(){
	this->picassoHelper->clearView();
	this->drawIsometricMap();
	this->drawDinamicEntities();
	this->drawStaticEntities();
	this->picassoHelper->renderView();
}

void JuegoVista::drawDinamicEntities(){
	pair<float,float>* screenPosition = juego->getProtagonista()->getScreenPosition();
	int offSetX = this->juego->getOffset()->first;
	int offSetY = this->juego->getOffset()->second;
	this->picassoHelper->renderObject(this->juego->getProtagonista()->getPathImage(), screenPosition->first - gameSettings->getTileSize()/2 + offSetX, screenPosition->second - juego->getProtagonista()->getLengthPixel() / 2 + offSetY, gameSettings->getTileSize(), gameSettings->getTileSize(), this->juego->getProtagonista()->getPositionOfSprite());
}

JuegoVista::JuegoVista(Juego* juego) {
	this->juego = juego;
	this->picassoHelper = PicassoHelper::GetInstance();
	this->picassoHelper->createContext();
}

JuegoVista::~JuegoVista() {
	this->picassoHelper->~PicassoHelper();
	//No ejecuto el destructor porque lo hace el GameController
	this->juego = NULL;
}


