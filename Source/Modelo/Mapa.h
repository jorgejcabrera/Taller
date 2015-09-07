/*
 * Mapa.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_MAPA_H_
#define SOURCE_MODELO_MAPA_H_

#include "EntidadPartida.h"
#include "Tile.h"
#include "DefaultSettings.h"
#include <iostream>
#include <map>
#include <list>


using namespace std;

class Mapa {
private:
	list<EntidadPartida> entidades;
	map<pair<int,int>,Tile> tiles;
public:
	Mapa();
	void show();
	Tile* getTileAt(int x,int y);
	map<pair<int,int>,Tile>* getTiles();
	virtual ~Mapa();
};


#endif /* SOURCE_MODELO_MAPA_H_ */
