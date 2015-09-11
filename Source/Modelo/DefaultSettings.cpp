/*
 * DefaultSettings.cpp
 *
 *  Created on: 4 de set. de 2015
 *      Author: jorge
 */

#include "DefaultSettings.h"

const string DefaultSettings::NOMBRE_ESCENARIO  = "Orleans";
const string DefaultSettings::IMAGE_BASE_PATH = "../Taller/Images";
const string DefaultSettings::AGE_OF_EMPIRES = "Industrial_Age";

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

bool DefaultSettings::isEntityTypeValid(const string &type){
	list<string> validTypes;

	//Medieval_age
	validTypes.push_back("Castle");
	validTypes.push_back("Town_Center");

	//Industrial_age
	validTypes.push_back("Consulate");
	validTypes.push_back("Town_Hall");
	validTypes.push_back("Church");

	bool found = (std::find(validTypes.begin(), validTypes.end(), type) != validTypes.end());
	return found;
}

string DefaultSettings::imagePathByTypeAndAge(const string &object,const string &age){
	if(isEntityTypeValid(object)){
		return IMAGE_BASE_PATH +"/"+age+"/"+object+".png";
	}
	return NULL;
}
string DefaultSettings::defaultImage(){
	return IMAGE_BASE_PATH +"white_tile.bmp";

}

string DefaultSettings::getAgeOfEmpires(){
	return AGE_OF_EMPIRES;
}

DefaultSettings::~DefaultSettings() {
}
