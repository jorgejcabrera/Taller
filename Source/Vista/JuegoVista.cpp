/*
 * JuegoVista.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "JuegoVista.h"

void JuegoVista::drawIsometricMap(const string &file){
	int posX = 0;
	int posY = 2;
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
    EntidadEstatica* castillo = new EntidadEstatica(DefaultSettings::getTileSize() * 6,DefaultSettings::getTileSize() * 4,"castle",true);
	int posY = 0 * castillo->getLength();
	int posX = 0 * castillo->getWidth() + DefaultSettings::getScreenWidth() / 2;

    picassoHelper->renderObject(castillo->getPathImage(),posX - 80, posY - 40,castillo->getWidth(), castillo->getLength());
    picassoHelper->renderView();
}

JuegoVista::~JuegoVista() {
	picassoHelper->~PicassoHelper();
}


