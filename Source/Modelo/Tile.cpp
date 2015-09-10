/*
 * Tile.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "Tile.h"

using namespace std;

Tile::Tile(int x, int y ) {
	this->position.first = x;
	this->position.second = y;
	this->superficie = superficie;
}

void Tile::pushSurface(surface_type surface){
	this->superficie = surface;
}

int Tile::getSurfaceSpeed(){
	return this->superficie;
}

pair<int,int>* Tile::getPosition(){
	return &this->position;
}

int Tile::getPosX(){
	return this->position.first;
}

int Tile::getPosY(){
	return this->position.second;
}

void Tile::show(){
	cout << "x:" << this->posX << ", y:" << this->posY << "\n";
}

Tile::~Tile() {
	// TODO Auto-generated destructor stub
}

