/*
 * Tile.h
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_TILE_H_
#define SOURCE_MODELO_TILE_H_



class Tile {
	int posX;
	int posY;
public:
	Tile(int x,int y);
	virtual ~Tile();
};

#endif /* SOURCE_MODELO_TILE_H_ */
