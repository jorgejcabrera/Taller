/*
 * JuegoVista.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "JuegoVista.h"

void JuegoVista::drawTiles(SDL_Texture *image, PicassoHelper* picassoHelper){
	int yTiles = DefaultSettings::getMapHeight() /  DefaultSettings::getTileSize();
	int cant = 0;
	int y = 0;
	int x = 0;

	//barrido vertical de los tiles
	for(int i=0; i <= yTiles * 2;i++){
		//me fijo la cantidad de tiles a dibujar segun la altura que este posicionado
		if( i > yTiles)
			cant = yTiles - ( i - yTiles - 1);
		else
			cant = i + 1;
		x = (DefaultSettings::getMapWidth() / 2) - (cant - 1) * DefaultSettings::getTileSize();

		//barrido horizontal de los tiles parte superior
		for(int j=0;j<cant;j++){
			picassoHelper->renderTexture(image, x, y,  DefaultSettings::getTileSize() * 2, DefaultSettings::getTileSize());
			x +=  DefaultSettings::getTileSize() * 2;
		}
		y +=  DefaultSettings::getTileSize() / 2;
	}
}

JuegoVista::JuegoVista() {
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


