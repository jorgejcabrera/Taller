/*
 * PicassoHelper.cpp
 *
 *  Created on: 6/9/2015
 *      Author: jorlando
 */

#include "PicassoHelper.h"

PicassoHelper::PicassoHelper() {
}

void PicassoHelper::createContext(){
		//inicializamos SDL
	    if (SDL_Init(SDL_INIT_VIDEO) != 0){
	    	this->exitError("Error SDL_Init:");
	    }
	    // creamos la ventana
	    window = SDL_CreateWindow("Age of empires", 100, 100, DefaultSettings::getScreenWidth(), DefaultSettings::getScreenHeight(), SDL_WINDOW_SHOWN);
	    if (window == NULL){
	    	this->exitError("SDL_CreateWindow Error:");
	    }
	    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	    if (renderer == NULL){
	    	this->exitError("SDL_CreateRenderer Error:");
	    }
}

SDL_Texture* PicassoHelper::loadTexture(const string &file){
	SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
	if (texture == NULL){
		this->exitError("loadTexture Error:");
	}
	listTexture.push_front(texture);
	return texture;
}

void PicassoHelper::renderTexture(SDL_Texture *tex, int x, int y, int w, int h){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(renderer, tex, NULL, &dst);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
}

PicassoHelper::~PicassoHelper() {
	for(list<SDL_Texture*>::iterator list_iter = listTexture.begin();list_iter != listTexture.end(); list_iter++){
		SDL_DestroyTexture(*list_iter);
	}
	if (renderer != NULL){
		SDL_DestroyRenderer(renderer);
	}
	if (window != NULL){
			SDL_DestroyWindow(window);
	}
	SDL_Quit();
}

void PicassoHelper::exitError(const string &message) {
	cout << message << " " << SDL_GetError() << endl;
	this->~PicassoHelper();
}

void PicassoHelper::renderView(){
	SDL_RenderPresent(renderer);
}

