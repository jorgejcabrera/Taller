/*
 * DefaultSettings.cpp
 *
 *  Created on: 4 de set. de 2015
 *      Author: jorge
 */

#include "DefaultSettings.h"

const string DefaultSettings::NOMBRE_ESCENARIO  = "Orleans";
const string DefaultSettings::IMAGE_BASE_PATH = "../Taller/Images/";

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

//void DefaultSettings::trasladarse(){}

bool DefaultSettings::isEntityTypeValid(const string &type){
	list<string> validTypes;
	validTypes.push_back("castillo");
	validTypes.push_back("arbol");

	bool found = (std::find(validTypes.begin(), validTypes.end(), type) != validTypes.end());
	return found;
}

string DefaultSettings::imagePathByType(const string &object){
	if(isEntityTypeValid(object)){
		return IMAGE_BASE_PATH +object+".png";
	}
	return NULL;
}
string DefaultSettings::defaultImage(){
	return IMAGE_BASE_PATH +"white_tile.bmp";

}

DefaultSettings::~DefaultSettings() {
}
