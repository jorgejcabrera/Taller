/*
 * PicassoHelper.cpp
 *
 *  Created on: 6/9/2015
 *      Author: jorlando
 */

#include "../../Headers/Modelo/PicassoHelper.h"
PicassoHelper* PicassoHelper::instance = NULL;

PicassoHelper::PicassoHelper() {
	this->window = NULL;
	this->renderer = NULL;
}

PicassoHelper::PicassoHelper(int width, int high) {
	this->window = NULL;
	this->renderer = NULL;
	this->widthView = width;
	this->highView = high;
}

void PicassoHelper::createContext(){
		//inicializamos SDL
	    if (SDL_Init(SDL_INIT_VIDEO) != 0){
	    	this->exitError("Error SDL_Init:");
	    }
	    // creamos la ventana
	    window = SDL_CreateWindow("Age of empires", 100, 100, this->widthView, this->highView, SDL_WINDOW_SHOWN);
	    if (window == NULL){
	    	this->exitError("SDL_CreateWindow Error:");
	    }
	    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	    if (renderer == NULL){
	    	this->exitError("SDL_CreateRenderer Error:");
	    }
	    TTF_Init();
   		this->font= TTF_OpenFont("Purisa-Bold.ttf", 100);
   		if(!font) {
   		    printf("TTF_OpenFont: %s\n", TTF_GetError());
   		}
}

void PicassoHelper::renderObject(const string &file, int x, int y, int w, int h){
		SDL_Texture* textureExists;
		map<string,SDL_Texture*>::iterator it = mapByImagePath.find( file.c_str());
		if(it != mapByImagePath.end()){
			textureExists = it->second;
		}else{
			textureExists = loadTexture(file);
		}
		SDL_SetTextureColorMod(textureExists, 255, 255, 255);
		renderTexture(textureExists,x,y,w,h);
}

//TODO revisar esto, tenemos 4 render object que casi hacen lo mismo
void PicassoHelper::renderObjectGrey(const string &file, int x, int y, int w, int h){
		SDL_Texture* textureExists;
		map<string,SDL_Texture*>::iterator it = mapByImagePath.find( file.c_str());
		if(it != mapByImagePath.end()){
			textureExists = it->second;
		}else{
			textureExists = loadTexture(file);
		}
		SDL_SetTextureColorMod(textureExists, 82, 82, 82);
		renderTexture(textureExists,x,y,w,h);
}

void PicassoHelper::renderObject(const string &file, int x, int y, int w, int h, bool available){
		SDL_Texture* textureExists;
		map<string,SDL_Texture*>::iterator it = mapByImagePath.find( file.c_str());
		if(it != mapByImagePath.end()){
			textureExists = it->second;
		}else{
			textureExists = loadTexture(file);
		}
		if(available){
			SDL_SetTextureColorMod(textureExists, 82, 223, 87);
		}else{
			SDL_SetTextureColorMod(textureExists, 255, 0, 0);
		}
		renderTexture(textureExists,x,y,w,h);
}

void PicassoHelper::renderObject(const string &file, int x, int y, int w, int h, SDL_Rect rectObject){
		SDL_Texture* textureExists;
		map<string,SDL_Texture*>::iterator it = mapByImagePath.find( file.c_str());
		if(it != mapByImagePath.end()){
			textureExists = it->second;
		}else{
			textureExists = loadTexture(file);
		}
		renderTexture(textureExists,x,y,w,h,rectObject);
}

SDL_Texture* PicassoHelper::loadTexture(const string &file){
	SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
	if (texture == NULL){
		cout << file << endl;
		this->exitError("loadTexture Error:");
	}
	this->mapByImagePath[file.c_str()] = texture;
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
}

void PicassoHelper::renderTexture(SDL_Texture *tex, int x, int y, int w, int h , SDL_Rect rectObject){
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(renderer, tex, &rectObject, &dst);
}

void PicassoHelper::exitError(const string &message) {
	cout << message << " " << SDL_GetError() << endl;
	this->~PicassoHelper();
}

void PicassoHelper::renderView(){
	SDL_RenderPresent(renderer);
}

void PicassoHelper::clearView(){
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer,0,0,0,1);
}

void PicassoHelper::renderBackgroud(){
	string file = DefaultSettings::getPathOfMenuBackground();
	SDL_Texture* backgroudTexture = this->loadTexture(file);
	SDL_RenderCopy(renderer, backgroudTexture, NULL, NULL);
}

PicassoHelper* PicassoHelper::GetInstance() {
	if (!instance) {
		instance = new PicassoHelper();
		instance->createContext();
	}
	return instance;
}

PicassoHelper* PicassoHelper::GetInstance(int width, int high) {
	if (!instance) {
		instance = new PicassoHelper(width,high);
		instance->createContext();
	}
	return instance;
}

void PicassoHelper::renderFogOfWar(const string &file, int x, int y, int w, int h) {
	SDL_Texture* textureExists;
	map<string,SDL_Texture*>::iterator it = mapByImagePath.find( file.c_str());
	if(it != mapByImagePath.end()){
		textureExists = (*it).second;
	}else{
		textureExists = loadTexture(file);
	}
	SDL_SetTextureAlphaMod(textureExists,150);
	renderTexture(textureExists,x,y,w,h);
}

void PicassoHelper::renderText(int x, int y, int w, int h, string text,Uint8 r, Uint8 g, Uint8 b) {
	SDL_Texture* textureExists;
	map<string,SDL_Texture*>::iterator it = mapByImagePath.find(text);
	if(it != mapByImagePath.end()){
		textureExists = it->second;
	}else{
		SDL_Surface* surface;
		SDL_Color color = {r,g,b};
		surface = TTF_RenderText_Solid(this->font, text.c_str(), color);
		textureExists = SDL_CreateTextureFromSurface(renderer, surface);
		this->mapByImagePath[text.c_str()] = textureExists;
		SDL_FreeSurface(surface);
	}
	renderTexture(textureExists,x,y,w,h);
}


PicassoHelper::~PicassoHelper() {
	for (map<string,SDL_Texture*>::iterator it=mapByImagePath.begin(); it!=mapByImagePath.end(); ++it){
		SDL_DestroyTexture(it->second);
		it->second=NULL;
	}

	if (renderer != NULL){
		SDL_DestroyRenderer(renderer);
		renderer=NULL;
	}
	if (window != NULL){
		SDL_DestroyWindow(window);
		window=NULL;
	}
	this->widthView = 0;
		this->highView = 0;
		this->instance=NULL;
	SDL_Quit();
	TTF_CloseFont(this->font);
	TTF_Quit();
}
