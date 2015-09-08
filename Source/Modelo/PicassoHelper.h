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
#include <list>

class PicassoHelper {
private:
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	list<SDL_Texture*> listTexture;
	PicassoHelper();
	static PicassoHelper* instance;
public:
	void createContext();
	SDL_Texture* loadTexture(const string &file);
	~PicassoHelper();
	void exitError(const string &message);
	void renderView();
	void renderTexture(SDL_Texture *tex, int x, int y, int w, int h);
	static PicassoHelper* GetInstance();
};

#endif /* MODELO_PICASSOHELPER_H_ */
