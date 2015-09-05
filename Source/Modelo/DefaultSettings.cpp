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
	this->SCREEN_WIDTH = 800;
	this->SCREEN_HEIGHT = 680;
	this->TILE_SIZE = 40;
	this->MARGEN_SCROLL = 30;
	this->NOMBRE_ESCENARIO = "Orleans";
	this->ESCENARIO_ANCHO = 100;
	this->ESCENARIO_ALTO = 100;

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
int DefaultSettings::getEscenarioAncho(){
	return this->ESCENARIO_ANCHO;
}
int DefaultSettings::getEscenarioAlto(){
	return this->ESCENARIO_ALTO;
}

void DefaultSettings::trasladarse(){}

void DefaultSettings::setTileSize(int value){
	this->TILE_SIZE = value;
}

DefaultSettings::~DefaultSettings() {
	// TODO Auto-generated destructor stub
}
