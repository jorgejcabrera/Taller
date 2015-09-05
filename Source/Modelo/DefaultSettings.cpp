/*
 * DefaultSettings.cpp
 *
 *  Created on: 4 de set. de 2015
 *      Author: jorge
 */

#include "DefaultSettings.h"

DefaultSettings::DefaultSettings() {
	// TODO Auto-generated constructor stub
	this->CONF_VEL_PERSONAJE;
	this->SCREEN_WIDTH = 1024;
	this->SCREEN_HEIGHT = 860;
	this->TILE_SIZE = 40;
	this->MARGEN_SCROLL = 30;
	this->NOMBRE_ESCENARIO = "Orleans";
	this->MAP_WIDTH = 800;
	this->MAP_HEIGHT = 680;

}

int DefaultSettings::getScreenWidth(){
	return this->SCREEN_WIDTH;
}
int DefaultSettings::getScreenHeight(){
	return this->SCREEN_HEIGHT;
}
int DefaultSettings::getTileSize(){
	return this->TILE_SIZE;
}
int DefaultSettings::getMargenScroll(){
	return this->MARGEN_SCROLL;
}
string DefaultSettings::getNombreEscenario(){
	return this->NOMBRE_ESCENARIO;
}
int DefaultSettings::getMapWidth(){
	return this->MAP_WIDTH;
}
int DefaultSettings::getMapHeight(){
	return this->MAP_HEIGHT;
}

void DefaultSettings::trasladarse(){}

void DefaultSettings::setTileSize(int value){
	this->TILE_SIZE = value;
}

DefaultSettings::~DefaultSettings() {
	// TODO Auto-generated destructor stub
}
