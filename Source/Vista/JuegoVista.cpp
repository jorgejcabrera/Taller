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
	for (map<pair<int,int>,Tile>::iterator it = this->mapa->getTiles()->begin(); it != this->mapa->getTiles()->end();++it){
		Tile* tileActual = &((*it).second);
		//transformo coordenadas cartesianas a isométricas
		posY = (tileActual->getPosX()+tileActual->getPosY()) * DefaultSettings::getTileSize() / 2;
		posX = (tileActual->getPosX()-tileActual->getPosY()) * DefaultSettings::getTileSize() + DefaultSettings::getScreenWidth() / 2;	//comienzo a dibujar de la mitad de la pantalla
		picassoHelper->renderObject(file,posX,posY,  DefaultSettings::getTileSize() * 2, DefaultSettings::getTileSize());
	}
}

JuegoVista::JuegoVista(Mapa* mapa) {
	this->mapa = mapa;
	picassoHelper = PicassoHelper::GetInstance();
	picassoHelper->createContext();
    string imagePath = "../Taller/Images/grass_new.png";
	drawIsometricMap(imagePath);

    // Agrego un castillo para probar el path de imagen y para ver como se muestra
    EntidadEstatica* castillo = new EntidadEstatica(3,2,"castillo",true);
    castillo->push(4,4);
    pair<int,int> isometricPosition = picassoHelper->getIsometricPosition(castillo);
    picassoHelper->renderObject(castillo->getPathImage(), isometricPosition.first , isometricPosition.second,castillo->getWidth() * 2 * DefaultSettings::getTileSize(), castillo->getLength() * DefaultSettings::getTileSize() * 2);

    EntidadEstatica* consulado = new EntidadEstatica(3,2,"consulado",true);
    consulado->push(10,9);
    pair<int,int> isometricPositionCon = picassoHelper->getIsometricPosition(consulado);
    picassoHelper->renderObject(consulado->getPathImage(), isometricPositionCon.first , isometricPositionCon.second,consulado->getWidth() * 2 * DefaultSettings::getTileSize(), consulado->getLength() * DefaultSettings::getTileSize() * 2);

    EntidadEstatica* edificio = new EntidadEstatica(3,2,"Town_Hall_(Industrial_Age)",true);
    edificio->push(9,2);
    isometricPositionCon = picassoHelper->getIsometricPosition(edificio);
    picassoHelper->renderObject(edificio->getPathImage(), isometricPositionCon.first , isometricPositionCon.second,edificio->getWidth() * 2 * DefaultSettings::getTileSize(), edificio->getLength() * DefaultSettings::getTileSize() * 2);

    picassoHelper->renderView();
}

JuegoVista::~JuegoVista() {
	picassoHelper->~PicassoHelper();
}


