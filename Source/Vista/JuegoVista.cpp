/*
 * JuegoVista.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "JuegoVista.h"

JuegoVista::JuegoVista() {
    //inicializamos SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
    	 cout << "Error SDL_Init:"  <<  SDL_GetError ();
    }

    // creamos la ventana
    SDL_Window *win = SDL_CreateWindow("Age of empires", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
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

	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_Rect rectangle;
	rectangle.x = 2;
	rectangle.y = 0.5;
	rectangle.w = 50;
	rectangle.h = 50;
	SDL_RenderFillRect(ren, &rectangle);

	SDL_RenderPresent(ren);

//
//    // Clean up
//    SDL_DestroyTexture(tex);
//    SDL_DestroyRenderer(ren);
//    SDL_DestroyWindow(win);
//    SDL_Quit();
}

JuegoVista::~JuegoVista() {
//    SDL_DestroyTexture(tex);
//    SDL_DestroyRenderer(ren);
//    SDL_DestroyWindow(win);
    SDL_Quit();
}
