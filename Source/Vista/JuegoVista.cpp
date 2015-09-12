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

JuegoVista::JuegoVista(Juego* juego) {
	this->juego = juego;
	picassoHelper = PicassoHelper::GetInstance(juego);
	picassoHelper->createContext();
    string imagePath = "../Taller/Images/grass_new.png";
	drawIsometricMap(imagePath);
	drawEntities();

    // Agrego un castillo para probar el path de imagen y para ver como se muestra
//    EntidadEstatica* castillo = new EntidadEstatica(DefaultSettings::getMediumSize(),DefaultSettings::getMediumSize(),"Consulate",true);
//    castillo->push(9,2);
//    pair<int,int> isometricPosition = picassoHelper->getIsometricPosition(castillo);
//    picassoHelper->renderObject(castillo->getPathImage(), isometricPosition.first , isometricPosition.second,castillo->getWidth() * 2 * DefaultSettings::getTileSize(), (castillo->getLength()-1) * DefaultSettings::getTileSize() * 2);
//
//    EntidadEstatica* torre = new EntidadEstatica(DefaultSettings::getMediumSize(),DefaultSettings::getMediumSize(),"Church",true);
//    torre->push(0,0);
//    isometricPosition = picassoHelper->getIsometricPosition(torre);
//    picassoHelper->renderObject(torre->getPathImage(), isometricPosition.first , isometricPosition.second,torre->getWidth() * 2 * DefaultSettings::getTileSize(), (torre->getLength()-1) * DefaultSettings::getTileSize() * 2);
//
//    EntidadEstatica* edificio = new EntidadEstatica(DefaultSettings::getMediumSize(),DefaultSettings::getMediumSize(),"Town_Hall",true);
//    edificio->push(2,10);
//    isometricPosition = picassoHelper->getIsometricPosition(edificio);
//    picassoHelper->renderObject(edificio->getPathImage(), isometricPosition.first , isometricPosition.second,edificio->getWidth() * 2 * DefaultSettings::getTileSize(), (edificio->getLength()-1) * DefaultSettings::getTileSize() * 2);

    picassoHelper->renderView();
}

JuegoVista::~JuegoVista() {
	picassoHelper->~PicassoHelper();
}


