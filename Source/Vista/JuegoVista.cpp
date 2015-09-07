/*
 * JuegoVista.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "JuegoVista.h"

void JuegoVista::drawTiles(SDL_Texture *image, PicassoHelper* picassoHelper){
	int posX = 0;
	int posY = 0;
	map<pair<int,int>,Tile>::iterator verticeInferior = this->mapa->getTiles()->end();
	int max = DefaultSettings::getTileSize() + DefaultSettings::getMapWidth() / 2;
	for (map<pair<int,int>,Tile>::iterator it = this->mapa->getTiles()->begin(); it != this->mapa->getTiles()->end();++it){
		Tile tileActual = (*it).second;
		posY = (tileActual.getPosX()+tileActual.getPosY()) * DefaultSettings::getTileSize() / 2;
		posX = (tileActual.getPosX()-tileActual.getPosY()) * DefaultSettings::getTileSize() + DefaultSettings::getScreenWidth() / 2;
		picassoHelper->renderTexture(image,posX,posY,  DefaultSettings::getTileSize() * 2, DefaultSettings::getTileSize());
	}
}

JuegoVista::JuegoVista(Mapa* mapa) {
	this->mapa = mapa;
	picassoHelper = new PicassoHelper();
	picassoHelper->createContext();
    string imagePath = "../Taller/Images/white_tile.bmp";
    SDL_Texture *image = picassoHelper->loadTexture(imagePath);
    drawTiles(image,picassoHelper);
    picassoHelper->renderView();
}

JuegoVista::~JuegoVista() {
	picassoHelper->~PicassoHelper();
}


