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
	for (map<pair<int,int>,Tile>::iterator it = this->juego->getMap()->getTiles()->begin(); it != this->juego->getMap()->getTiles()->end();++it){
		Tile* tileActual = &((*it).second);
		//transformo coordenadas cartesianas a isométricas
		posY = (tileActual->getPosX()+tileActual->getPosY()) * DefaultSettings::getTileSize() / 2;
		posX = (tileActual->getPosX()-tileActual->getPosY()) * DefaultSettings::getTileSize() + DefaultSettings::getScreenWidth() / 2;	//comienzo a dibujar de la mitad de la pantalla
		picassoHelper->renderObject(file,posX,posY,  DefaultSettings::getTileSize() * 2, DefaultSettings::getTileSize());
	}
}

JuegoVista::JuegoVista(Juego* juego) {
	this->juego = juego;
	picassoHelper = PicassoHelper::GetInstance(juego);
	picassoHelper->createContext();
    string imagePath = "../Taller/Images/grass_new.png";
	drawIsometricMap(imagePath);

    // Agrego un castillo para probar el path de imagen y para ver como se muestra
    EntidadEstatica* castillo = new EntidadEstatica(3,2,"Consulate",true);
    castillo->push(4,4);
    pair<int,int> isometricPosition = picassoHelper->getIsometricPosition(castillo);
    picassoHelper->renderObject(castillo->getPathImage(), isometricPosition.first , isometricPosition.second,castillo->getWidth() * 2 * DefaultSettings::getTileSize(), castillo->getLength() * DefaultSettings::getTileSize() * 2);

    EntidadEstatica* torre = new EntidadEstatica(3,2,"Church",true);
    torre->push(7,10);
    isometricPosition = picassoHelper->getIsometricPosition(torre);
    picassoHelper->renderObject(torre->getPathImage(), isometricPosition.first , isometricPosition.second,torre->getWidth() * 2 * DefaultSettings::getTileSize(), torre->getLength() * DefaultSettings::getTileSize() * 2);

    EntidadEstatica* edificio = new EntidadEstatica(3,2,"Town_Hall",true);
    edificio->push(9,2);
    isometricPosition = picassoHelper->getIsometricPosition(edificio);
    picassoHelper->renderObject(edificio->getPathImage(), isometricPosition.first , isometricPosition.second,edificio->getWidth() * 2 * DefaultSettings::getTileSize(), edificio->getLength() * DefaultSettings::getTileSize() * 2);


    picassoHelper->renderView();
}

JuegoVista::~JuegoVista() {
	picassoHelper->~PicassoHelper();
}


