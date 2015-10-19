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
#include "../../Headers/Modelo/GameSettings.h"
#include "../../Headers/Modelo/PicassoHelper.h"
#include "../../Headers/Control/UtilsController.h"
#include "../../Headers/Modelo/DefaultSettings.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <list>
#include "TileVista.h"
#include "EntidadEstaticaVista.h"
#include "EntidadSemiEstaticaVista.h"
#include "EntidadDinamicaVista.h"

using namespace std;

class JuegoVista {
private:
	GameSettings* gameSettings;
	PicassoHelper* picassoHelper;
	pair<int,int> offset;
	void drawIsometricMap();
	void drawStaticEntities(int runCycles);
	void drawDinamicEntities(int runCycles);
	list<TileVista*> tiles;
	map<int, EntidadEstaticaVista*> buildings;
	map<int, EntidadSemiEstaticaVista*> semiEstaticos;
	map<int, EntidadDinamicaVista*> personajes;

public:
	void render(int ciclos);
	JuegoVista();
	~JuegoVista();
	void createView();
	void actualizarOffset(int offsetX,int offsetY);
	pair<int,int>* getOffset();
	void addTile(string surface, int x, int y);
	void addBuilding(int id, string type, int x, int y);
	void addSemiEstatico(int id, string type, int x, int y);
	void addPersonaje(int id, string type, int x, int y);

};

#endif /* SOURCE_VISTA_JUEGOVISTA_H_ */
