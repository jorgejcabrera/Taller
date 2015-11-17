/*
 * Mapa.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_MAPA_H_
#define SOURCE_MODELO_MAPA_H_

#include "EntidadPartida.h"
#include "EntidadEstatica.h"
#include "EntidadSemiEstatica.h"
#include "Tile.h"
#include "DefaultSettings.h"
#include "GameSettings.h"
#include "../Control/UtilsController.h"
#include "Resource.h"
#include <iostream>
#include <map>
#include <list>


using namespace std;

class Mapa {
private:
	list<EntidadPartida*> entidades;
	list<Resource*> resources;
	map<pair<int,int>,Tile*> tiles;
	GameSettings* gameSettings;
	/*
	* genera recursos de manera ramdom
	* */
	void createResources();

public:
	Mapa();
	/*
	* devuelve una posicion disponible
	* */
	pair<int,int> getAvailablePosition();
	/*
	* Devuelve una posicion disponible cercana al origen que recibe
	* */
	pair<int,int> getAvailablePosition(int xFrom, int yFrom);
	Tile* getTileAt(int x,int y);
	/*
	* devuelve una lista de novedades de recursos que sufrieron un cambio
	* */
	list<Message*> getResourcesMessages();
	list<Resource*>* getResources();
	list<EntidadPartida*>* getEntities();
	map<pair<int,int>,Tile*>* getTiles();
	void pushEntity(EntidadPartida* entidad);
	void deleteEntity(int id);
	bool positionAvailable(EntidadPartida* entidad);
	~Mapa();
};


#endif /* SOURCE_MODELO_MAPA_H_ */
