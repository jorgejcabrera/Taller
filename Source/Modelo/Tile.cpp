/*
 * Tile.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "Tile.h"

using namespace std;

Tile::Tile(int x, int y) {
	this->posX = x;
	this->posY = y;
}

void Tile::show(){
	cout << "x:" << this->posX << ", y:" << this->posY << "\n";
}

Tile::~Tile() {
	// TODO Auto-generated destructor stub
}

