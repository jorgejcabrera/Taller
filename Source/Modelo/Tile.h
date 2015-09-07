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

using namespace std;

class Tile {
	int posX;
	int posY;
public:
	Tile(int x,int y);
	void show();
	virtual ~Tile();
};

#endif /* SOURCE_MODELO_TILE_H_ */
