/*
 * DefaultSettings.cpp
 *
 *  Created on: 4 de set. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/DefaultSettings.h"

const string DefaultSettings::NOMBRE_ESCENARIO  = "Orleans";
const string DefaultSettings::IMAGE_BASE_PATH = "../../Taller/Images";
const string DefaultSettings::IMAGE_TILES_PATH = "Tiles";
const string DefaultSettings::IMAGE_PERSONAJES_PATH = "Personajes";
const string DefaultSettings::AGE_OF_EMPIRES = "Industrial_Age";
const string DefaultSettings::TIPO_PROTAGONISTA = "soldado";
const string DefaultSettings::NAME_OF_CIVIC_CENTER = "Barracks";

DefaultSettings::DefaultSettings() {
}

int DefaultSettings::getTimeOut(){
	return TIMEOUT;
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

int DefaultSettings::getLimiteDerecho() {
	double factor = TILE_SIZE * TILE_SIZE - (17 / 16);
	int altura = sqrt(factor);
	int widthMapaIsometric = altura * 2 * MAP_WIDTH;
	if (widthMapaIsometric > SCREEN_WIDTH) {
		return ((SCREEN_WIDTH - widthMapaIsometric) / 2) - TILE_SIZE;
	} else {
		return 0;
	}
}

int DefaultSettings::getLimiteIzquierdo() {
	double factor = TILE_SIZE * TILE_SIZE - (17 / 16);
	int altura = sqrt(factor);
	int widthMapaIsometric = altura * 2 * MAP_WIDTH;
	if (widthMapaIsometric > SCREEN_WIDTH) {
		return ((widthMapaIsometric - SCREEN_WIDTH) / 2) - TILE_SIZE;
	} else {
		return 0;
	}
}

int DefaultSettings::getLimiteInferior() {
	double factor = TILE_SIZE * TILE_SIZE - (17 / 16);
	int altura = sqrt(factor);
	int heightMapaIsometric = altura * MAP_HEIGHT;
	if (heightMapaIsometric > SCREEN_HEIGHT) {
		return (SCREEN_HEIGHT - heightMapaIsometric);
	} else {
		return TILE_SIZE/2;
	}
}

int DefaultSettings::getLimiteSuperior() {
	return 0;
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
	string tipo = getTypeEntity(type);
	return (tipo!="");
}

string DefaultSettings::getTypeEntity(const string &type){
	list<string> edificios;
	//Social
	edificios.push_back("Castle");
	edificios.push_back("Town_Center");
	edificios.push_back("Public_Bath");
	edificios.push_back("Consulate");
	edificios.push_back("Church");
	edificios.push_back("AdvancedChurch");
	edificios.push_back("House1");
	edificios.push_back("House2");
	edificios.push_back("Market");
	edificios.push_back("Tabern");
	edificios.push_back("castillo");

	//Desarrollo
	edificios.push_back("University");
	edificios.push_back("Factory");
	edificios.push_back("Armory");
	edificios.push_back("Smithy");

	//Ejercito
	edificios.push_back("Army");
	edificios.push_back("Barracks");
	edificios.push_back("Town_Hall");
	if(isInList(edificios,type))
		return "edificios";

	list<string> semiestaticos;
	semiestaticos.push_back("molino");
	if(isInList(semiestaticos,type))
		return "semiestaticos";

	list<string> personajes;
	personajes.push_back("soldado");
	personajes.push_back("king");
	personajes.push_back("villager");
	if(isInList(personajes,type))
		return "personajes";

	list<string> tiles;
		tiles.push_back("pasto");
		tiles.push_back("ceramico");
		tiles.push_back("hielo");
		tiles.push_back("tierra");
		tiles.push_back("agua");
		if(isInList(tiles,type))
			return "tiles";

		list<string> resources;
		resources.push_back("gold");
		resources.push_back("chori");
		resources.push_back("wood");
		if(isInList(resources,type))
				return "resources";
	return "";
}

list<string> DefaultSettings::getListOfAttributesCanSetByType(const string &type){
	list<string> attributes;
	attributes.push_back("imagen");
	if(type == "edificios"){
		attributes.push_back("ancho_base");
		attributes.push_back("alto_base");
	}else if (type == "personajes"){
		attributes.push_back("fps");
		attributes.push_back("delay");
	}
	return attributes;
}

bool DefaultSettings::isInList(list<string> listOfThings, const string &type){
	return (std::find(listOfThings.begin(), listOfThings.end(), type) != listOfThings.end());
}

string DefaultSettings::imagePathBuildingsByTypeAndAge(const string &object,const string &age){
	if(isEntityTypeValid(object)){
		return IMAGE_BASE_PATH +"/"+age+"/"+object+".png";
	}
	return defaultImage();
}
string DefaultSettings::defaultImage(){
	return IMAGE_BASE_PATH +"/Tiles/" +"white_tile.bmp";

}

string DefaultSettings::imagePathPersonajesByType(const string &object){
	if(isEntityTypeValid(object)){
		return IMAGE_BASE_PATH+"/"+IMAGE_PERSONAJES_PATH+"/"+object+".png";
	}
	return defaultImage();
}

string DefaultSettings::imagePathTilesByType(const string &object){
	if(isEntityTypeValid(object)){
			return IMAGE_BASE_PATH+"/"+IMAGE_TILES_PATH+"/"+object+".png";
		}
	return defaultImage();
}

string DefaultSettings::getTipoProtagonista(){
	return TIPO_PROTAGONISTA;
}
int DefaultSettings::getPosXProtagonista(){
	return POS_X_PROTAGONISTA;
}
int DefaultSettings::getPosYProtagonista(){
	return POS_Y_PROTAGONISTA;
}

int DefaultSettings::getVelocidadPersonaje	(){
	return VELOCIDAD_PERSONAJE;
}

int DefaultSettings::getRangeVisibility() {
	return RANGE_VISIBILITY;
}

int DefaultSettings::getQtyInitialCharacters(){
	return QTY_INITIAL_CHARACTERS;
}

string DefaultSettings::getNameCivicCenter(){
	return NAME_OF_CIVIC_CENTER;
}

DefaultSettings::~DefaultSettings() {
}
