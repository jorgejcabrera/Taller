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
#include "../Modelo/Juego.h"
#include "../Modelo/PicassoHelper.h"
#include "../Modelo/EntidadEstatica.h"
#include "SDL2/SDL_image.h"
#include "../Modelo/GameSettings.h"

#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

class JuegoVista {
private:
	PicassoHelper* picassoHelper;
	Juego* juego;
	GameSettings* gameSettings;
	void drawIsometricMap();
	void drawStaticEntities();
	void drawDinamicEntities();
public:
	void render();
	JuegoVista(Juego* juego);
	~JuegoVista();

};

#endif /* SOURCE_VISTA_JUEGOVISTA_H_ */
