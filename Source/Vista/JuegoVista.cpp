/*
 * JuegoVista.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "JuegoVista.h"
#include "SDL2/SDL_image.h"


SDL_Texture* loadTexture(const string &file, SDL_Renderer *ren){
	//SDL_Surface *bmp = SDL_LoadBMP(file.c_str());
	//SDL_SetColorKey( bmp ,SDL_SRCCOLORKEY, SDL_MapRGB( bmp->format, 0, 0, 0) );
	//SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == NULL){
		cout << "loadTexture Error: " << SDL_GetError() << std::endl;
	}
	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}

void drawTopTiles(int cant,SDL_Texture *image, SDL_Renderer *ren){
	int x = SCREEN_WIDTH / 2 - (cant - 1) * TILE_SIZE / 2;
	int y = (cant - 1) * TILE_SIZE / 2;
	for(int i=0;i<cant;i++){
		renderTexture(image, ren, x, y, TILE_SIZE,TILE_SIZE);
		x += TILE_SIZE;
	}
}

void drawLowerTiles(int cant,SDL_Texture *image, SDL_Renderer *ren){
	int x = SCREEN_WIDTH / 2 - (cant - 1) * TILE_SIZE / 2;
	int y = SCREEN_HEIGHT - (cant - 1) * TILE_SIZE / 2;
	for(int i=0;i<cant;i++){
		renderTexture(image, ren, x, y, TILE_SIZE,TILE_SIZE);
		x += TILE_SIZE;
	}
}

JuegoVista::JuegoVista() {

    //inicializamos SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
    	 cout << "Error SDL_Init:"  <<  SDL_GetError ();
    }

    // creamos la ventana
    SDL_Window *win = SDL_CreateWindow("Age of empires", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
    //string backgroundPath = "../Taller/Images/grass_only.bmp";
    //SDL_Texture *background = loadTexture(backgroundPath, ren);
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

    //Tiling the Background

    //Determine how many tiles we'll need to fill the screen
    //sint xTiles = SCREEN_WIDTH / TILE_SIZE;
    int yTiles = SCREEN_HEIGHT / TILE_SIZE;
    int aux;

    //Draw the tiles by calculating their positions
    for (int i = 0; i < yTiles; i++){
    	aux = i;
    	drawTopTiles(++aux,image,ren);
    	drawLowerTiles(++aux,image,ren);
    }

    //Drawing the Foreground
    /*int iW, iH;
    SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;
    renderTexture(image, ren, x, y);*/

    SDL_RenderPresent(ren);
    SDL_Delay(2000);

    // Clean up
    //SDL_DestroyTexture(background);
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


