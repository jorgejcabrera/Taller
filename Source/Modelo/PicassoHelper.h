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
#include "SDL2/SDL_image.h"
#include <iostream>
#include <map>

class PicassoHelper {
private:
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	PicassoHelper();
	static PicassoHelper* instance;
	map<string,SDL_Texture*> mapByImagePath;
	void renderTexture(SDL_Texture *tex, int x, int y, int w, int h);
	SDL_Texture* loadTexture(const string &file);

public:
	void createContext();
	~PicassoHelper();
	void exitError(const string &message);
	void renderView();
	void renderObject(const string &file, int x, int y, int w, int h);
	static PicassoHelper* GetInstance();
};

#endif /* MODELO_PICASSOHELPER_H_ */
