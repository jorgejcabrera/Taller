/*
 * GameSettings.cpp
 *
 *  Created on: 19/9/2015
 *      Author: nico
 */

#include "GameSettings.h"

GameSettings* GameSettings::instance = NULL;

namespace std {

GameSettings::GameSettings() {
	loader = new Loader();
}

int GameSettings::getScreenWidth(){
	return DefaultSettings::getScreenWidth();

}
int GameSettings::getScreenHeight(){
	return DefaultSettings::getScreenHeight();
}
int GameSettings::getTileSize(){
	return DefaultSettings::getTileSize();
}
int GameSettings::getLongMargenScroll(){
	return DefaultSettings::getLongMargenScroll();
}
string GameSettings::getNombreEscenario(){
	return DefaultSettings::getNombreEscenario();
}
int GameSettings::getMapWidth(){
	return DefaultSettings::getMapWidth();
}
int GameSettings::getMapHeight(){
	return DefaultSettings::getMapHeight();
}

int GameSettings::getMediumSize(){
	return DefaultSettings::getMediumSize();
}

int GameSettings::getVelocidadScrollUno(){
	return DefaultSettings::getVelocidadScrollUno();
}

int GameSettings::getVelocidadScrollDos(){
	return DefaultSettings::getVelocidadScrollDos();
}

int GameSettings::getLimiteDerecho() {
	return DefaultSettings::getLimiteDerecho();
}

int GameSettings::getLimiteIzquierdo() {
	return DefaultSettings::getLimiteIzquierdo();
}

int GameSettings::getLimiteInferior() {
	return DefaultSettings::getLimiteInferior();
}

int GameSettings::getLimiteSuperior() {
	return DefaultSettings::getLimiteSuperior();
}

int GameSettings::getMargenDerechoUno(){
	return DefaultSettings::getMargenDerechoUno();
}

int GameSettings::getMargenDerechoDos(){
	return DefaultSettings::getMargenDerechoDos();
}

int GameSettings::getMargenIzquierdoUno(){
return DefaultSettings::getMargenIzquierdoUno();
}

int GameSettings::getMargenIzquierdoDos(){
return DefaultSettings::getMargenIzquierdoDos();
}

int GameSettings::getMargenSuperiorUno(){
return DefaultSettings::getMargenSuperiorUno();
}

int GameSettings::getMargenSuperiorDos(){
return DefaultSettings::getMargenSuperiorDos();
}

int GameSettings::getMargenInferiorUno(){
return DefaultSettings::getMargenInferiorUno();
}

int GameSettings::getMargenInferiorDos(){
return DefaultSettings::getMargenInferiorDos();
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

	//Personajes
	validTypes.push_back("soldado");

	//Tiles
	validTypes.push_back("grass");
	validTypes.push_back("ceramic");
	validTypes.push_back("hielo");
	validTypes.push_back("sand");

	bool found = (std::find(validTypes.begin(), validTypes.end(), type) != validTypes.end());
	return found;
}

string DefaultSettings::imagePathBuildingsByTypeAndAge(const string &object,const string &age){
	if(isEntityTypeValid(object)){
		return IMAGE_BASE_PATH +"/"+age+"/"+object+".png";
	}
	return NULL;
}
string DefaultSettings::defaultImage(){
	return IMAGE_BASE_PATH +"/Tiles/" +"white_tile.bmp";

}

string DefaultSettings::imagePathPersonajesByType(const string &object){
	if(isEntityTypeValid(object)){
			return IMAGE_BASE_PATH+"/"+IMAGE_PERSONAJES_PATH+"/"+object+".png";
		}
		return NULL;
}

string DefaultSettings::imagePathTilesByType(const string &object){
	if(isEntityTypeValid(object)){
			return IMAGE_BASE_PATH+"/"+IMAGE_TILES_PATH+"/"+object+".png";
		}
		return NULL;
}

string DefaultSettings::getAgeOfEmpires(){
	return AGE_OF_EMPIRES;
}

void GameSettings::SetGameSettings(){
	loader->load();
}

GameSettings* GameSettings::GetInstance() {
	if (!instance) {
		instance = new GameSettings();
		instance->SetGameSettings();
	}
	return instance;
}

GameSettings::~GameSettings() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
