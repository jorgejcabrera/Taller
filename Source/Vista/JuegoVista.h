/*
 * JuegoVista.h
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_VISTA_JUEGOVISTA_H_
#define SOURCE_VISTA_JUEGOVISTA_H_

#include "SDL2/SDL.h"
#include "../Modelo/DefaultSettings.h"
#include "SDL2/SDL_image.h"

#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

class JuegoVista {
private:
	DefaultSettings* defaultSettings = new DefaultSettings();
public:
	JuegoVista();
	virtual ~JuegoVista();
private:
	SDL_Texture* loadTexture(const string &file, SDL_Renderer *ren);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
	void drawTopTiles(int cant,SDL_Texture *image, SDL_Renderer *ren);
	void drawLowerTiles(int cant,SDL_Texture *image, SDL_Renderer *ren);
	int getCountTiles();
};

#endif /* SOURCE_VISTA_JUEGOVISTA_H_ */
