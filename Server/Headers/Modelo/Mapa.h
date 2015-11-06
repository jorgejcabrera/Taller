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
#include <iostream>
#include <map>
#include <list>


using namespace std;

class Mapa {
private:
	list<EntidadPartida*> entidades;
	map<pair<int,int>,Tile*> tiles;
	GameSettings* gameSettings;
public:
	Mapa();
	Tile* getTileAt(int x,int y);
	void pushEntity(EntidadPartida* entidad);
	bool positionAvailable(EntidadPartida* entidad);
	map<pair<int,int>,Tile*>* getTiles();
	list<EntidadPartida*>* getEntities();
	//EntidadPartida* getEntityAt(int x,int y);
	~Mapa();

	//Busco una posicion disponible para poner un personaje cuando se crea un cliente
	pair<int,int> getAvailablePosition();
};


#endif /* SOURCE_MODELO_MAPA_H_ */
