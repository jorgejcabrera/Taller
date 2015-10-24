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
#include "../Utils/Logger.h"
#include "MenuVista.h"
#include "MiniMapVista.h"

using namespace std;

class JuegoVista {
private:
	GameSettings* gameSettings;
	PicassoHelper* picassoHelper;
	MenuVista* menuVista;
	MiniMapVista* miniMapVista;
	/*
	*offset correspondiente al desplazamiento por el offset
	**/
	pair<int,int> offset;
	void drawIsometricMap();
	void drawStaticEntities(int runCycles);
	void drawDinamicEntities(int runCycles);
	void drawSemiStaticsEntities(int runCycles);
	void drawMenu();
	void drawMiniMap();
	list<TileVista*> tiles;
	map<int, EntidadEstaticaVista*> buildings;
	map<int, EntidadSemiEstaticaVista*> semiEstaticos;
	map<int, EntidadDinamicaVista*> personajes;
	map<int, EntidadDinamicaVista*> misPersonajes;

public:
	JuegoVista();
	/*
	*metodo que se encarga de dibujar mapa y todas las entidades
	**/
	void render(int ciclos);
	void createView();
	void actualizarOffset(int offsetX,int offsetY);
	pair<int,int>* getOffset();
	void addTile(string surface, int x, int y);
	void addBuilding(int id, string type, int x, int y);
	void addSemiEstaticEntity(int id, string type, int x, int y);
	void addDinamicEntity(int id, string type, int x, int y, bool imTheOwner, int active);
	map<int,EntidadDinamicaVista*>* getMyEntities();
	EntidadDinamicaVista* getEntityById(int id);
	~JuegoVista();


};

#endif /* SOURCE_VISTA_JUEGOVISTA_H_ */
