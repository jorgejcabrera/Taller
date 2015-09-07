/*
 * DefaultSettings.cpp
 *
 *  Created on: 4 de set. de 2015
 *      Author: jorge
 */

#include "DefaultSettings.h"

const std::string DefaultSettings::NOMBRE_ESCENARIO  = "Orleans";

DefaultSettings::DefaultSettings() {
}

int DefaultSettings::getScreenWidth(){
	return SCREEN_WIDTH;
}

int DefaultSettings::getScreenHeight(){
	return SCREEN_HEIGHT;
}
int DefaultSettings::getTileSize(){
	return TILE_SIZE;
}
int DefaultSettings::getMargenScroll(){
	return MARGEN_SCROLL;
}
string DefaultSettings::getNombreEscenario(){
	return NOMBRE_ESCENARIO;
}
int DefaultSettings::getMapWidth(){
	return MAP_WIDTH;
}
int DefaultSettings::getMapHeight(){
	return MAP_HEIGHT;
}

void DefaultSettings::trasladarse(){}

/*void DefaultSettings::setTileSize(int value){
	TILE_SIZE = value;
}*/

DefaultSettings::~DefaultSettings() {
}
