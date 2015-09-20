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


bool GameSettings::isEntityTypeValid(const string &type){
	return DefaultSettings::isEntityTypeValid(type);
}

string GameSettings::imagePathBuildingsByTypeAndAge(const string &object,const string &age){
	return DefaultSettings::imagePathBuildingsByTypeAndAge(object,age);
}

string GameSettings::defaultImage(){
	return DefaultSettings::defaultImage();
}

string GameSettings::imagePathPersonajesByType(const string &object){
	return DefaultSettings::imagePathPersonajesByType(object);
}

string GameSettings::imagePathTilesByType(const string &object){
	return DefaultSettings::imagePathTilesByType(object);
}

string GameSettings::getAgeOfEmpires(){
	return DefaultSettings::getAgeOfEmpires();
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
