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
	this->SCREEN_HEIGHT = -1;
	this->SCREEN_WIDTH = -1;

}

int GameSettings::getScreenWidth(){
	return (SCREEN_WIDTH > 1) ? SCREEN_WIDTH : DefaultSettings::getScreenWidth();
}

int GameSettings::getScreenHeight(){
	return (SCREEN_HEIGHT > 1) ? SCREEN_HEIGHT : DefaultSettings::getScreenHeight();
}

int GameSettings::getTileSize(){
	return DefaultSettings::getTileSize();
}

int GameSettings::getLongMargenScroll(){
	return (LONG_MARGEN_SCROLL > 1) ? LONG_MARGEN_SCROLL : DefaultSettings::getLongMargenScroll();
}

string GameSettings::getNombreEscenario(){
	return (NOMBRE_ESCENARIO == "") ? NOMBRE_ESCENARIO : DefaultSettings::getNombreEscenario();
}

int GameSettings::getMapWidth(){
	return (MAP_WIDTH > 0 ) ? MAP_WIDTH : DefaultSettings::getMapWidth();
}

int GameSettings::getMapHeight(){
	return (MAP_HEIGHT > 0 ) ? MAP_HEIGHT : DefaultSettings::getMapHeight();
}

int GameSettings::getMediumSize(){
	return (MEDIUM_SIZE > 0 ) ? MEDIUM_SIZE : DefaultSettings::getMediumSize();
}

int GameSettings::getVelocidadScrollUno(){
	return (VELOCIDAD_SCROLL_UNO > 0) ? VELOCIDAD_SCROLL_UNO : DefaultSettings::getVelocidadScrollUno();
}

int GameSettings::getVelocidadScrollDos(){
	return (VELOCIDAD_SCROLL_DOS > 0) ? VELOCIDAD_SCROLL_DOS : DefaultSettings::getVelocidadScrollDos();
}

int GameSettings::getLimiteDerecho() {
	double factor = this->getTileSize() * this->getTileSize() - (17 / 16);
	int altura = sqrt(factor);
	int widthMapaIsometric = altura * 2 * this->getMapWidth();
	if (widthMapaIsometric > this->getScreenWidth()) {
		return ((this->getScreenWidth() - widthMapaIsometric) / 2) - this->getTileSize();
	} else {
		return 0;
	}
}

int GameSettings::getLimiteIzquierdo() {
	double factor = this->getTileSize() * this->getTileSize() - (17 / 16);
	int altura = sqrt(factor);
	int widthMapaIsometric = altura * 2 * this->getMapWidth();
	if (widthMapaIsometric > this->getScreenWidth()) {
		return ((widthMapaIsometric - this->getScreenWidth()) / 2) - this->getTileSize();
	} else {
		return 0;
	}
}

int GameSettings::getLimiteInferior() {
	double factor = this->getTileSize() * this->getTileSize() - (17 / 16);
	int altura = sqrt(factor);
	int heightMapaIsometric = altura * this->getMapHeight();
	if (heightMapaIsometric > this->getScreenHeight()) {
		return (this->getScreenHeight() - heightMapaIsometric);
	} else {
		return this->getTileSize()/2;
	}
}

int GameSettings::getLimiteSuperior() {
	return DefaultSettings::getLimiteSuperior();
}

int GameSettings::getMargenDerechoUno(){
	return ( this->getScreenWidth() - this->getLongMargenScroll() * 2);
}

int GameSettings::getMargenDerechoDos(){
	return (this->getScreenWidth() - this->getLongMargenScroll());
}

int GameSettings::getMargenIzquierdoUno(){
	return this->getLongMargenScroll() * 2;
}

int GameSettings::getMargenIzquierdoDos(){
	return this->getLongMargenScroll();
}

int GameSettings::getMargenSuperiorUno(){
	return this->getLongMargenScroll() * 2;
}

int GameSettings::getMargenSuperiorDos(){
	return this->getLongMargenScroll() * 2;
}

int GameSettings::getMargenInferiorUno(){
	return (this->getScreenHeight() - 2 * this->getLongMargenScroll());
}


int GameSettings::getMargenInferiorDos(){
	return (this->getScreenHeight() - this->getLongMargenScroll());
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
	map<string,int>* mapSI = new map<string,int>();
	vector< map< string, string> >* vectorMSS = new vector< map< string, string> >();
	map< string, string> * mapSS = new map< string, string>();

	loader->load();

	mapSI = loader->getScreen();
	this->SCREEN_HEIGHT = mapSI->operator []("ancho");
	this->SCREEN_WIDTH = mapSI->operator []("alto");
	mapSI->clear();

}

GameSettings* GameSettings::GetInstance() {
	if (!instance) {
		instance = new GameSettings();
		instance->SetGameSettings();
	}
	return instance;
}

GameSettings::~GameSettings() {
//	GameSettings* GameSettings::instance = NULL;
}

} /* namespace std */
