/*
 * JuegoVista.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "JuegoVista.h"

void JuegoVista::drawIsometricMap(const string &file){
	int posX = 0;
	int posY = 0;
	for (map<pair<int,int>,Tile*>::iterator it = this->juego->getMap()->getTiles()->begin(); it != this->juego->getMap()->getTiles()->end();++it){
		Tile* tileActual = (*it).second;
		//transformo coordenadas cartesianas a isométricas
		posY = (tileActual->getPosX()+tileActual->getPosY()) * DefaultSettings::getTileSize() / 2;
		posX = (tileActual->getPosX()-tileActual->getPosY()) * DefaultSettings::getTileSize() + DefaultSettings::getScreenWidth() / 2;	//comienzo a dibujar de la mitad de la pantalla
		picassoHelper->renderObject(file,posX,posY,  DefaultSettings::getTileSize() * 2, DefaultSettings::getTileSize());
	}
}

void JuegoVista::drawEntities(){
	pair<int,int> isometricPosition;
	for(map<pair<int,int>,EntidadPartida*>::iterator it=this->juego->getMap()->getEntities()->begin();it!=this->juego->getMap()->getEntities()->end();++it){
		EntidadPartida* entidad = (*it).second;
		isometricPosition = picassoHelper->getIsometricPosition(entidad);
		picassoHelper->renderObject(entidad->getPathImage(), isometricPosition.first , isometricPosition.second,entidad->getWidth() * 2 * DefaultSettings::getTileSize(), (entidad->getLength()-1) * DefaultSettings::getTileSize() * 2);
	}
}

void JuegoVista::render(){

	picassoHelper->setFondo();

	string imagePath = "../Taller/Images/grass_new.png";
	drawIsometricMap(imagePath);
	drawEntities();
	picassoHelper->renderView();
}

JuegoVista::JuegoVista(Juego* juego) {
	this->juego = juego;
	picassoHelper = PicassoHelper::GetInstance(juego);
	picassoHelper->createContext();

}

JuegoVista::~JuegoVista() {
	picassoHelper->~PicassoHelper();
}


