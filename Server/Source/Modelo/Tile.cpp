/*
 * Tile.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/Tile.h"

using namespace std;

Tile::Tile(int x, int y ) {
	this->position.first = x;
	this->position.second = y;
	this->available = true;
	this->superficie = grass;
	this->superficieStr ="pasto";
}

string Tile::getSuperficie(){
	return this->superficieStr;
}

void Tile::setSuperficie(string superficieNueva){
	this->superficieStr = superficieNueva;
}

void Tile::changeStatusAvailable(){
	stringstream ss;
	ss << "Tile [" << this->position.first <<";"<< this->position.second<<"] was available " << this->available;
	Logger::get()->logDebug("Tile","changeStatusAvailable",ss.str());
	ss.str("");
	bool result = this->available == false;
	ss << "Tile [" << this->position.first <<";"<< this->position.second<<"] now is " << result;
	Logger::get()->logDebug("Tile","changeStatusAvailable",ss.str());
	this->available = this->available == false;
}

bool Tile::isAvailable(){
	return this->available;
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

Tile::~Tile() {
}
