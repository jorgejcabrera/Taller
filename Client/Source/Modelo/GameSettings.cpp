/*
 * GameSettings.cpp
 *
 *  Created on: 19/9/2015
 *      Author: nico
 */

#include "../../Headers/Modelo/GameSettings.h"

GameSettings* GameSettings::instance = NULL;

namespace std {

GameSettings::GameSettings() {
}

int GameSettings::getScreenWidth(){
	if((SCREEN_WIDTH<=0) or (SCREEN_WIDTH>DefaultSettings::getScreenWidth()))
		return DefaultSettings::getScreenWidth();
	return this->SCREEN_WIDTH;
}

int GameSettings::getScreenHeight(){
	if((SCREEN_HEIGHT<=0) or (SCREEN_HEIGHT>DefaultSettings::getScreenHeight()))
		return DefaultSettings::getScreenHeight();
	return this->SCREEN_HEIGHT;
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
	//return (VELOCIDAD_SCROLL_UNO > 0) ? VELOCIDAD_SCROLL_UNO : DefaultSettings::getVelocidadScrollUno();
	return DefaultSettings::getVelocidadScrollUno();
}

int GameSettings::getVelocidadScrollDos(){
	//return (VELOCIDAD_SCROLL_DOS > 0) ? VELOCIDAD_SCROLL_DOS : DefaultSettings::getVelocidadScrollDos();
	return DefaultSettings::getVelocidadScrollDos();
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

GameSettings* GameSettings::GetInstance() {
	if (!instance) {
		instance = new GameSettings();
	}
	return instance;
}

map<pair<int,int>,string> GameSettings::getTiles(){
	return this->tiles;
}

string GameSettings::getValueInMap(map<string,string> myMap, const string &key){
	map<string,string>::iterator iterador2 = myMap.find(key);
		if (iterador2 != myMap.end()){
				return iterador2->second;
	 }
	 return "";
}

map<string,string> GameSettings::getValueInVector(vector < map<string,string> > myVector, const string &key, const string &value){
	map<string,string> objeto;
	for(vector< map< string, string> >::iterator it = myVector.begin(); it!= myVector.end(); ++it){
				string keyValue = this->getValueInMap(*it, key);
				if(keyValue==value){
					objeto = *it;
				}
		}
	 return objeto;
}

bool GameSettings::isFileExist(const string fileName){
    std::ifstream infile(fileName.c_str());
    return infile.good();
}

GameSettings::~GameSettings() {
	this->instance =NULL;
}

void GameSettings::setScreenDimension(int width, int heigth){
	this->SCREEN_WIDTH = width;
	this->SCREEN_HEIGHT = heigth;
}

void GameSettings::addEntityConfig(EntidadConfig* entidad){
	this->entitiesConfig.insert(make_pair(entidad->getName(),entidad));
}

EntidadConfig* GameSettings::getEntityConfig(string nameEntity){
	return this->entitiesConfig.at(nameEntity);
}

void GameSettings::setMapDimention(int ancho, int alto){
	this->MAP_WIDTH=ancho;
	this->MAP_HEIGHT=alto;

}

int GameSettings::getAlturaMenuInferior() {
	return DefaultSettings::getAlturaMenuInferior();
}

string GameSettings::getPathOfFoggedTile(){
	return DefaultSettings::getPathOfFoggedTile();
}

string GameSettings::getPathOfCoveredTile(){
	return DefaultSettings::getPathOfCoveredTile();
}

int GameSettings::getRangeVisibility() {
	return DefaultSettings::getRangeVisibility(); // TODO que cada entidad tenga su propia visibilidad, y que esto se obtenga del yaml
}

map<string,int> GameSettings::getCostsOf(string type) {
	return DefaultSettings::getCostsOf(type);	
}

} /* namespace std */
