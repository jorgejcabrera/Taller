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
#include "Tile.h"
#include "DefaultSettings.h"
#include "GameSettings.h"
#include <iostream>
#include <map>
#include <list>


using namespace std;

class Mapa {
private:
	map<pair<int,int>,EntidadPartida*> entidades;
	map<pair<int,int>,Tile*> tiles;
	GameSettings* gameSettings;
public:
	Mapa();
	void show();
	Tile* getTileAt(int x,int y);
	void pushEntity(EntidadPartida* entidad);
	bool positionAvailable(EntidadPartida* entidad);
	EntidadPartida* getEntityAt(int x,int y);
	map<pair<int,int>,Tile*>* getTiles();
	map<pair<int,int>,EntidadPartida*>* getEntities();
	virtual ~Mapa();
};


#endif /* SOURCE_MODELO_MAPA_H_ */
