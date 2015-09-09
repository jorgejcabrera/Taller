/*
 * Tile.h
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_TILE_H_
#define SOURCE_MODELO_TILE_H_

#include <string>
#include <iostream>
#include "EntidadPartida.h"
using namespace std;

//indica el porcentaje de la velocidad con la que se mueve el personaje
enum surface_type{
	grass = 100,
	water = 50,
	land = 90,
	sand = 20
};

class Tile {
	int posX;
	int posY;
	surface_type superficie = grass;	//por default la superficie es pasto
	EntidadPartida* entidad = NULL;
public:
	Tile(int x,int y);
	void show();
	int getPosX();
	int getPosY();
	void pushEntity(EntidadPartida* entidad);
	EntidadPartida* getEntity();
	void pushSurface(surface_type surface);
	int getSurfaceSpeed();
	virtual ~Tile();
};

#endif /* SOURCE_MODELO_TILE_H_ */
