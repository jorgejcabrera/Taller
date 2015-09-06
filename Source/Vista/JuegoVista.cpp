/*
 * JuegoVista.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "JuegoVista.h"

SDL_Texture* JuegoVista::loadTexture(const string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == NULL){
		cout << "loadTexture Error: " << SDL_GetError() << std::endl;
	}
	return texture;
}

void JuegoVista::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
}

void JuegoVista::drawTiles(SDL_Texture *image, SDL_Renderer *ren){
	int yTiles = defaultSettings->getMapHeight() /  defaultSettings->getTileSize();
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
		x = (defaultSettings->getMapWidth() / 2) - (cant - 1) * defaultSettings->getTileSize();

		//barrido horizontal de los tiles parte superior
		for(int j=0;j<cant;j++){
			renderTexture(image, ren, x, y,  defaultSettings->getTileSize() * 2, defaultSettings->getTileSize());
			x +=  defaultSettings->getTileSize() * 2;
		}
		y +=  defaultSettings->getTileSize() / 2;
	}
}

JuegoVista::JuegoVista() {

    //inicializamos SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
    	 cout << "Error SDL_Init:"  <<  SDL_GetError ();
    }

    // creamos la ventana
    SDL_Window *win = SDL_CreateWindow("Age of empires", 100, 100, defaultSettings->getScreenWidth(), defaultSettings->getScreenHeight(), SDL_WINDOW_SHOWN);
    if (win == NULL){
    	cout << "SDL_CreateWindow Error: " << SDL_GetError();
    	SDL_Quit();
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL){
    	SDL_DestroyWindow(win);
    	cout << "SDL_CreateRenderer Error: " << SDL_GetError();
    	SDL_Quit();
    }

    string imagePath = "../Taller/Images/white_tile.bmp";
    SDL_Texture *image = loadTexture(imagePath, ren);
    if (/*background == NULL ||*/ image == NULL){
    	SDL_DestroyRenderer(ren);
    	SDL_DestroyWindow(win);
    	//SDL_DestroyTexture(background);
    	SDL_DestroyTexture(image);
    	cout << "loadTexture Error: " << SDL_GetError() << std::endl;
    	SDL_Quit();
    }

    //dibujamos los tiles del mapa
    drawTiles(image,ren);

    SDL_RenderPresent(ren);
    SDL_Delay(20000);

    // Clean up
    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

JuegoVista::~JuegoVista() {
//    SDL_DestroyTexture(tex);
//    SDL_DestroyRenderer(ren);
//    SDL_DestroyWindow(win);
    SDL_Quit();
}


