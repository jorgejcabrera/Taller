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
#include "../Modelo/Mapa.h"
#include "../Modelo/PicassoHelper.h"
#include "SDL2/SDL_image.h"

#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

class JuegoVista {
private:
	PicassoHelper* picassoHelper;
	Mapa* mapa;
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
	void drawTiles(SDL_Texture *image, PicassoHelper* picassoHelper);
	int getCountTiles();
public:
	JuegoVista(Mapa* mapaActual);
	~JuegoVista();

};

#endif /* SOURCE_VISTA_JUEGOVISTA_H_ */
