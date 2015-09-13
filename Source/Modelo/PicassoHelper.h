/*
 * PicassoHelper.h
 *
 *  Created on: 6/9/2015
 *      Author: jorlando
 */

#ifndef MODELO_PICASSOHELPER_H_
#define MODELO_PICASSOHELPER_H_

#include "SDL2/SDL.h"
#include "../Modelo/DefaultSettings.h"
#include "../Modelo/Juego.h"
#include "EntidadPartida.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <map>
#include <fstream>

class PicassoHelper {
private:
	Juego* juego;
	SDL_Window *window;
	SDL_Renderer *renderer;
	PicassoHelper(Juego* juego);
	static PicassoHelper* instance;
	map<string,SDL_Texture*> mapByImagePath;
	void renderTexture(SDL_Texture *tex, int x, int y, int w, int h);
	SDL_Texture* loadTexture(const string &file);
	bool isFileExist(const string fileName);

public:
	void createContext();
	~PicassoHelper();
	pair<int,int> getIsometricPosition(EntidadPartida* entidad);
	void exitError(const string &message);
	void renderView();
	void clearView();
	void renderObject(const string &file, int x, int y, int w, int h);
	static PicassoHelper* GetInstance(Juego* juego);
};

#endif /* MODELO_PICASSOHELPER_H_ */
