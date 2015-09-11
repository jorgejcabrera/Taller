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
    EntidadEstatica* castillo = new EntidadEstatica(3,2,"Castle",true);
    castillo->push(4,4);
    pair<int,int> isometricPosition = picassoHelper->getIsometricPosition(castillo);
    picassoHelper->renderObject(castillo->getPathImage(), isometricPosition.first , isometricPosition.second,castillo->getWidth() * 2 * DefaultSettings::getTileSize(), castillo->getLength() * DefaultSettings::getTileSize() * 2);

    picassoHelper->renderView();
}

JuegoVista::~JuegoVista() {
	picassoHelper->~PicassoHelper();
}


