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
#include "../../Headers/Modelo/ResourceCounter.h"
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
	* */
	pair<int,int> offset;
	/*
	*colección de recursos a ser consumidos
	* */
	map<pair<int,int>,int> resoursesToConsume;
	/*
	*entidades del mapa
	* */
	list<TileVista*> tiles;
	map<int, EntidadEstaticaVista*> buildings;
	map<int, EntidadSemiEstaticaVista*> semiEstaticos;
	map<int, EntidadDinamicaVista*> personajes;
	map<int, EntidadDinamicaVista*> misPersonajes;
	/*
	*métodos para renderizar el juego
	* */
	void drawIsometricMap();
	void drawStaticEntities(int runCycles);
	void drawDinamicEntities(int runCycles);
	void drawDinamicEntity(EntidadDinamicaVista* entity,int runCycles,bool isMyEntity);
	void drawSemiStaticsEntities(int runCycles);
	void drawMenu();
	void drawMiniMap();
	void drawFog();

public:
	JuegoVista();
	/*
	*metodo que se encarga de dibujar mapa y todas las entidades
	* */
	void render(int ciclos, ResourceCounter* resourceCounter);
	/*
	*agrega un recurso que será consumido cuando la entidad ocupe el correspondiente tile
	* */
	void addResourceToConsume(int id);
	/*
	*si hay algún recurso para consumir en la posicion pasada como parametro devuelve el id del 
	*recurso, caso contrario devuelve 0
	* */
	int consumeResource(int posX,int posY);
	/*
	*?
	* */
	void createView();
	void actualizarOffset(int offsetX,int offsetY);
	void setResources(int alimento, int madera, int oro);
	pair<int,int>* getOffset();
	void addTile(string surface, int x, int y);
	void addBuilding(int id, string type, int x, int y);
	void addSemiEstaticEntity(int id, string type, int x, int y);
	void addDinamicEntity(int id, string type, int x, int y, bool imTheOwner, int active);
	map<int,EntidadDinamicaVista*>* getMyEntities();
	map<int,EntidadDinamicaVista*>* getPersonajes();
	EntidadDinamicaVista* getEntityById(int id);
	void deleteStaticEntityById(int id);
	void setVisibleTile(int x,int y);
	bool isEntitySeen(pair<int,int>* entityPos, int lenght);
	/*
	*?
	* */
	map<string,string> entityInThisPosition(int x, int y);
	/*
	*?
	* */
	map<string,string> buildMapWithEntityData(EntidadPartidaVista* entidad);
	void setFoggedTiles();
	/*
	*?
	* */
	bool isEnemyEntityVisible(pair< int, int> pos);
	MenuVista* getMenuVista();
	void drawResources(ResourceCounter* resourceCounter);
	~JuegoVista();


};

#endif /* SOURCE_VISTA_JUEGOVISTA_H_ */
