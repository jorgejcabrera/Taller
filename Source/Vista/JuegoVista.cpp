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
	dst.w = w + 40;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
}

void JuegoVista::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}

void JuegoVista::drawTopTiles(int cant,SDL_Texture *image, SDL_Renderer *ren){
	int x = (defaultSettings->getScreenWidth() / 2) - (cant - 1) * (defaultSettings->getTileSize() / 2 + 20);
	int y = (cant - 1) *  defaultSettings->getTileSize() / 2;
	//barrido horizontal de los tiles
	for(int i=0;i<cant;i++){
		renderTexture(image, ren, x, y,  defaultSettings->getTileSize(), defaultSettings->getTileSize());
		x +=  defaultSettings->getTileSize() + 40;
	}
}

void JuegoVista::drawLowerTiles(int cant,SDL_Texture *image, SDL_Renderer *ren){
	int x = (defaultSettings->getScreenWidth() / 2) - (cant - 1) * (defaultSettings->getTileSize() / 2 + 20);
	int y = defaultSettings->getScreenHeight() - (cant - 1) *  defaultSettings->getTileSize() / 2 -  defaultSettings->getTileSize();
	//barrido horizontal de los tiles
	for(int i=0;i<cant;i++){
		renderTexture(image, ren, x, y,  defaultSettings->getTileSize(), defaultSettings->getTileSize());
		x +=  defaultSettings->getTileSize() + 40;
	}
}

int JuegoVista::getCountTiles(){
	int cant = defaultSettings->getScreenHeight() %  defaultSettings->getTileSize();
	if ( cant == 0)
		return defaultSettings->getScreenHeight() /  defaultSettings->getTileSize();
	else{
		while(cant != 0){
			int aux = defaultSettings->getTileSize() - 1;
			defaultSettings->setTileSize(aux);
			cant = defaultSettings->getScreenHeight() %  defaultSettings->getTileSize();
		}
		return cant;
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
    //Make sure they both loaded ok
    if (/*background == NULL ||*/ image == NULL){
    	SDL_DestroyRenderer(ren);
    	SDL_DestroyWindow(win);
    	//SDL_DestroyTexture(background);
    	SDL_DestroyTexture(image);
    	cout << "loadTexture Error: " << SDL_GetError() << std::endl;
    	SDL_Quit();
    }

    int yTiles = defaultSettings->getScreenHeight() /  defaultSettings->getTileSize();
    int aux;

    //Draw the tiles by calculating their positions
    for (int i = 0; i < yTiles; i++){
    	aux = i;
    	drawTopTiles(++aux,image,ren);
    	if ( i < yTiles - 1 ){
    		aux = i;
    		drawLowerTiles(++aux,image,ren);
    	}

    }

    SDL_RenderPresent(ren);
    SDL_Delay(20000000);

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


