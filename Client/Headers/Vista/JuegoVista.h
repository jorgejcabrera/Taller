/*
 * JuegoVista.h
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#ifndef HEADERS_VISTA_JUEGOVISTA_H_
#define HEADERS_VISTA_JUEGOVISTA_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "EntidadEstaticaVista.h"
#include "../../Headers/Modelo/GameSettings.h"
#include "../../Headers/Modelo/PicassoHelper.h"
#include "../../Headers/Control/UtilsController.h"
#include "../../Headers/Modelo/DefaultSettings.h"
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

class JuegoVista {
private:
	GameSettings* gameSettings;
	PicassoHelper* picassoHelper;
	pair<int,int> offset;
	void drawIsometricMap();
	void drawStaticEntities(int runCycles);
	void drawDinamicEntities(int runCycles);
public:
	void render(int ciclos);
	JuegoVista();
	~JuegoVista();
	void actualizarOffset(int offsetX,int offsetY);
	pair<int,int>* getOffset();

};

#endif /* SOURCE_VISTA_JUEGOVISTA_H_ */
