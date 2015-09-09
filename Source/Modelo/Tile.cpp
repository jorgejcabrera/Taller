/*
 * Tile.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "Tile.h"

using namespace std;

Tile::Tile(int x, int y ) {
	this->posX = x;
	this->posY = y;
	this->superficie = superficie;
}

void Tile::pushSurface(surface_type surface){
	this->superficie = surface;
}

int Tile::getSurfaceSpeed(){
	return this->superficie;
}

void Tile::pushEntity(EntidadPartida* entidad){
	this->entidad = entidad;
}

EntidadPartida* Tile::getEntity(){
	return this->entidad;
}

int Tile::getPosX(){
	return this->posX;
}

int Tile::getPosY(){
	return this->posY;
}

void Tile::show(){
	cout << "x:" << this->posX << ", y:" << this->posY << "\n";
}

Tile::~Tile() {
	// TODO Auto-generated destructor stub
}

