/*
 * JuegoVista.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "JuegoVista.h"


SDL_Texture* loadTexture(const string &file, SDL_Renderer *ren){
	SDL_Surface *bmp = SDL_LoadBMP(file.c_str());
	SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, bmp);

//	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == NULL){
		std::cout << "loadTexture Error: " << SDL_GetError() << std::endl;
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
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}

void drawTopTiles(int cant,int xTiles,SDL_Texture *image, SDL_Renderer *ren, int tile_size){
	int x = cant % xTiles;
	int y = cant / xTiles;
	for(int i=0;i<cant;i++){
		renderTexture(image, ren, x * tile_size, y * tile_size, tile_size,tile_size);
	}
}

JuegoVista::JuegoVista() {

	const int SCREEN_WIDTH  = 640;
	const int SCREEN_HEIGHT = 480;
	const int TILE_SIZE = 40;

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
    	std::cout << "loadTexture Error: " << SDL_GetError() << std::endl;
    	SDL_Quit();
    }

    //Tiling the Background

    //Determine how many tiles we'll need to fill the screen
    int xTiles = SCREEN_WIDTH / TILE_SIZE;
    int yTiles = SCREEN_HEIGHT / TILE_SIZE;

    //Draw the tiles by calculating their positions
    for (int i = 0; i < SCREEN_HEIGHT /TILE_SIZE ; ++i){
    	//int x = i % xTiles;
    	//int y = i / xTiles;
    	//renderTexture(image, ren, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE,TILE_SIZE);
    	drawTopTiles(i++,xTiles,image,ren,TILE_SIZE);
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


