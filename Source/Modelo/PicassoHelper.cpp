/*
 * PicassoHelper.cpp
 *
 *  Created on: 6/9/2015
 *      Author: jorlando
 */

#include "PicassoHelper.h"
PicassoHelper* PicassoHelper::instance = NULL;

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

void PicassoHelper::renderObject(const string &file, int x, int y, int w, int h){
		SDL_Texture* textureExists;
		map<string,SDL_Texture*>::iterator it = mapByImagePath.find( file.c_str());
		if(it != mapByImagePath.end()){
			textureExists = it->second;
		}else{
			textureExists = loadTexture(file);
		}
		renderTexture(textureExists,x,y,w,h);
}

SDL_Texture* PicassoHelper::loadTexture(const string &file){
	string fileImage = file.c_str();
	if(!(isFileExist(fileImage)))
		fileImage = DefaultSettings::defaultImage();

	SDL_Texture *texture = IMG_LoadTexture(renderer, fileImage.c_str());
	if (texture == NULL){
		this->exitError("loadTexture Error:");
	}
	this->mapByImagePath[fileImage.c_str()] = texture;
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
	for (map<string,SDL_Texture*>::iterator it=mapByImagePath.begin(); it!=mapByImagePath.end(); ++it){
		SDL_DestroyTexture(it->second);
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

PicassoHelper* PicassoHelper::GetInstance() {
	if (!instance) {
		instance = new PicassoHelper();
	}
	return instance;
}

pair<int,int> PicassoHelper::getIsometricPosition(EntidadPartida* entidad){
	int posY = 0 * entidad->getLength()  - ( entidad->getLength() - 1) * DefaultSettings::getTileSize() ;
	int posX = 0 * entidad->getWidth() + DefaultSettings::getScreenWidth() / 2 -  ( entidad->getWidth() - 1) * DefaultSettings::getTileSize();
	pair<int,int> isometricPosition;
	isometricPosition.first = posX;
	isometricPosition.second = posY;
	return isometricPosition;
}

bool PicassoHelper::isFileExist(const string fileName){
    std::ifstream infile(fileName.c_str());
    return infile.good();
}
