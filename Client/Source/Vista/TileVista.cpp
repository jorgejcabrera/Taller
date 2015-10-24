/*
 * TileVista.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "../../Headers/Vista/TileVista.h"

using namespace std;

TileVista::TileVista(int x, int y ) {
	this->position.first = x;
	this->position.second = y;
	this->seen = 0;
}

pair<int,int>* TileVista::getPosition(){
	return &this->position;
}

int TileVista::getPosX(){
	return this->position.first;
}

int TileVista::getPosY(){
	return this->position.second;
}

string TileVista::getPathImage(){
	return pathImage;
}

void TileVista::setPathImage(string path){
	this->pathImage = path;
}

bool TileVista::getSeen() {
	return this->seen;
}

void TileVista::saw() {
	this->seen = true;
}

TileVista::~TileVista() {
}
