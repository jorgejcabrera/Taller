/*
 * PicassoHelper.cpp
 *
 *  Created on: 6/9/2015
 *      Author: jorlando
 */

#include "PicassoHelper.h"
PicassoHelper* PicassoHelper::instance = NULL;

PicassoHelper::PicassoHelper() {
	this->window = NULL;
}

void PicassoHelper::createContext(){
		//inicializamos SDL
	    if (SDL_Init(SDL_INIT_VIDEO) != 0){
	    	this->exitError("Error SDL_Init:");
	    }

	    //cargamos la conf. del archivo yaml

	    loader = Loader::GetInstance();

	    // creamos la ventana
	    cout << "LOADER: " << loader->getScreenWidth() << loader->getScreenHeight() << endl;
//	    window = SDL_CreateWindow("Age of empires", 100, 100, loader->getScreenWidth(), loader->getScreenHeight(), SDL_WINDOW_SHOWN);
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
}

void PicassoHelper::renderTexture(SDL_Texture *tex, int x, int y, int w, int h , SDL_Rect rectObject){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(renderer, tex, &rectObject, &dst);
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

void PicassoHelper::clearView(){
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer,0,0,0,1);
}

PicassoHelper* PicassoHelper::GetInstance() {
	if (!instance) {
		instance = new PicassoHelper();
	}
	return instance;
}

pair<int,int> PicassoHelper::getIsometricPosition(EntidadPartida* entidad){
	pair<int,int> isometricPosition;
	//hacemos coincidir el vertice superior izquierdo de la entidad con el tile
	isometricPosition.first = (entidad->getPosition()->first - entidad->getPosition()->second) * DefaultSettings::getTileSize() + DefaultSettings::getScreenWidth() / 2;
	isometricPosition.second = (entidad->getPosition()->first + entidad->getPosition()->second) * DefaultSettings::getTileSize() / 2  ;

	//ahora hay que centrar la entidad con el tile
	isometricPosition.first = isometricPosition.first - (entidad->getWidth()-1)  *  DefaultSettings::getTileSize();
	isometricPosition.second = isometricPosition.second - (entidad->getLength()-1) *  DefaultSettings::getTileSize() / 2;
	return isometricPosition;
}

bool PicassoHelper::isFileExist(const string fileName){
    std::ifstream infile(fileName.c_str());
    return infile.good();
}
