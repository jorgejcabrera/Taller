/*
 * Tile.h
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_TILE_H_
#define SOURCE_MODELO_TILE_H_

#include "../Utils/Logger.h"
#include "../Utils/Socket/Message.h"
#include <string>
#include <iostream>

using namespace std;

//indica el porcentaje de la velocidad con la que se mueve el personaje
enum surface_type{
	grass = 100,
	water = 50,
	land = 90,
	sand = 20
};


class Tile {
	bool available;
	pair<int,int> position;
	//TODO: no usamos para nada la superficie
	surface_type superficie;	//por default la superficie es pasto
	string superficieStr;

public:
	Tile(int x,int y);
	void setPathImage(string path);
	void changeStatusAvailable();
	void setSuperficie(string superficieNueva);
	void pushSurface(surface_type surface);
	bool isAvailable();
	pair<int,int> getPosition();
	int getSurfaceSpeed();
	string getSuperficie();
	string getPathImage();
	Message* getMessage();
	virtual ~Tile();
};

#endif /* SOURCE_MODELO_TILE_H_ */
