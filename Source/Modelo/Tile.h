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
#include "DefaultSettings.h"

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
	surface_type superficie;	//por default la superficie es pasto
	string pathImage;
	void setPathImage(string path);

public:
	Tile(int x,int y);
	void show();
	void changeStatusAvailable();
	bool isAvailable();
	int getPosX();
	int getPosY();
	pair<int,int>* getPosition();
	void pushSurface(surface_type surface);
	int getSurfaceSpeed();
	virtual ~Tile();
	string getPathImage();
};

#endif /* SOURCE_MODELO_TILE_H_ */
