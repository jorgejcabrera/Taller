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
int DefaultSettings::getLongMargenScroll(){
	return LONG_MARGEN_SCROLL;
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

int DefaultSettings::getMediumSize(){
	return MEDIUM_SIZE;
}

int DefaultSettings::getVelocidadScrollUno(){
	return VELOCIDAD_SCROLL_UNO;
}

int DefaultSettings::getVelocidadScrollDos(){
	return VELOCIDAD_SCROLL_DOS;
}

int DefaultSettings::getLimiteDerecho(){
	return -SCREEN_WIDTH / 10;
}

int DefaultSettings::getLimiteIzquierdo(){
return  SCREEN_WIDTH / 10;
}

int DefaultSettings::getLimiteInferior(){
return - SCREEN_HEIGHT / 10;
}

int DefaultSettings::getLimiteSuperior(){
	return SCREEN_HEIGHT / 10;
}

int DefaultSettings::getMargenDerechoUno(){
return SCREEN_WIDTH - LONG_MARGEN_SCROLL * 2;
}

int DefaultSettings::getMargenDerechoDos(){
return SCREEN_WIDTH - LONG_MARGEN_SCROLL;
}

int DefaultSettings::getMargenIzquierdoUno(){
return LONG_MARGEN_SCROLL * 2;
}

int DefaultSettings::getMargenIzquierdoDos(){
return LONG_MARGEN_SCROLL;
}

int DefaultSettings::getMargenSuperiorUno(){
return LONG_MARGEN_SCROLL * 2;
}

int DefaultSettings::getMargenSuperiorDos(){
return LONG_MARGEN_SCROLL;
}

int DefaultSettings::getMargenInferiorUno(){
return SCREEN_HEIGHT - 2 * LONG_MARGEN_SCROLL;
}

int DefaultSettings::getMargenInferiorDos(){
return SCREEN_HEIGHT - LONG_MARGEN_SCROLL;
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
