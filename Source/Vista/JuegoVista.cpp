/*
 * JuegoVista.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "JuegoVista.h"

void JuegoVista::drawIsometricMap(){
	int posX = 0;
	int posY = 0;
	int offsetX = this->juego->getOffset()->first;
	int offsetY = this->juego->getOffset()->second;
	for (map<pair<int,int>,Tile*>::iterator it = this->juego->getMap()->getTiles()->begin(); it != this->juego->getMap()->getTiles()->end();++it){
		Tile* tileActual = (*it).second;
		//transformo coordenadas cartesianas a isométricas
		posY = (tileActual->getPosX()+tileActual->getPosY()) * DefaultSettings::getTileSize() / 2 + offsetY;
		posX = (tileActual->getPosX()-tileActual->getPosY()) * DefaultSettings::getTileSize() + DefaultSettings::getScreenWidth() / 2 + offsetX;	//comienzo a dibujar de la mitad de la pantalla
		this->picassoHelper->renderObject(tileActual->getPathImage(),posX,posY,  DefaultSettings::getTileSize() * 2, DefaultSettings::getTileSize());
	}
}

void JuegoVista::drawStaticEntities(){
	pair<int,int> isometricPosition;
	int offSetX = this->juego->getOffset()->first;
	int offSetY = this->juego->getOffset()->second;

	for(map<pair<int,int>,EntidadPartida*>::iterator it=this->juego->getMap()->getEntities()->begin();it!=this->juego->getMap()->getEntities()->end();++it){
		EntidadPartida* entidad = (*it).second;
		isometricPosition = this->picassoHelper->getIsometricPosition(entidad);
		this->picassoHelper->renderObject(entidad->getPathImage(), (isometricPosition.first+ offSetX) , (isometricPosition.second+ offSetY) ,entidad->getWidth() * 2 * DefaultSettings::getTileSize(), (entidad->getLength()-1) * DefaultSettings::getTileSize() * 2);
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
	this->picassoHelper->renderObject(this->juego->getProtagonista()->getPathImage(), screenPosition->first - DefaultSettings::getTileSize()/2 + offSetX, screenPosition->second - juego->getProtagonista()->getLengthPixel() / 2 + offSetY, DefaultSettings::getTileSize(), DefaultSettings::getTileSize(), this->juego->getProtagonista()->getPositionOfSprite());
}

JuegoVista::JuegoVista(Juego* juego) {
	this->juego = juego;
	this->picassoHelper = PicassoHelper::GetInstance();
	this->picassoHelper->createContext();
}

JuegoVista::~JuegoVista() {
	this->picassoHelper->~PicassoHelper();
}


