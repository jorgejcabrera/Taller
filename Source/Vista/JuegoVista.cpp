/*
 * JuegoVista.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "JuegoVista.h"

using namespace std;

JuegoVista::JuegoVista() {

    SDL_Window *window;                    // Declare a pointer

    //inicializamos SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
    	 cout << "Error SDL_Init:"  <<  SDL_GetError ();
    	 return;
    }

    // creamos la ventana
    SDL_Window *win = SDL_CreateWindow("Age of empires", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == NULL){
    	cout << "SDL_CreateWindow Error: " << SDL_GetError();
    	SDL_Quit();
    	return;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL){
    	SDL_DestroyWindow(win);
    	cout << "SDL_CreateRenderer Error: " << SDL_GetError();
    	SDL_Quit();
    	return;
    }

    string imagePath = "/home/jorge/Escritorio/Taller/image.bmp";
    SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
    if (bmp == NULL){
    	SDL_DestroyRenderer(ren);
    	SDL_DestroyWindow(win);
    	cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
    	SDL_Quit();
    	return;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == NULL){
    	SDL_DestroyRenderer(ren);
    	SDL_DestroyWindow(win);
    	std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    	SDL_Quit();
    	return;
    }

    //Dibujamos la textura
    for (int i = 0; i < 3; ++i){
    	//First clear the renderer
    	SDL_RenderClear(ren);
    	//Draw the texture
    	SDL_RenderCopy(ren, tex, NULL, NULL);
    	//Update the screen
    	SDL_RenderPresent(ren);
    	//Take a quick break after all that hard work
    	SDL_Delay(1000);
    }

    // Clean up
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

JuegoVista::~JuegoVista() {
	// TODO Auto-generated destructor stub
}
