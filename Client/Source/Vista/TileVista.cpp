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
	this->seen = false;
}

pair<int,int> TileVista::getPosition(){
	return this->position;
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

bool TileVista::getFogged() {
	return this->fogged;
}

void TileVista::setFogged(bool state) {
	this->fogged = state;
}

TileVista::~TileVista() {
}
