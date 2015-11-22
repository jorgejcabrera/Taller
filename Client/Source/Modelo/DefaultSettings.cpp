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
const string DefaultSettings::PATH_OF_FOGGED_TILE = "tileFog";
const string DefaultSettings::PATH_OF_COVERED_TILE = "tileNegro";
const string DefaultSettings::PATH_MENU_BACKGROUND = "../../Taller/Images/Menu/agePortada.jpg";

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

	edificios.push_back("flag");
	if(isInList(edificios,type))
		return "edificios";

	list<string> semiestaticos;
	semiestaticos.push_back("molino");
	if(isInList(semiestaticos,type))
		return "semiestaticos";

	list<string> personajes;
	personajes.push_back("soldado");
	personajes.push_back("soldadoSolo");
	personajes.push_back("aldeanoSolo");
	personajes.push_back("king");
	personajes.push_back("aldeano");
	personajes.push_back("cobra");
	personajes.push_back("caballo");
	personajes.push_back("cobraSolo");
	personajes.push_back("caballoSolo");
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

string DefaultSettings::getAgeOfEmpires(){
	return AGE_OF_EMPIRES;
}

int DefaultSettings::getViewDistance() {
	return VIEW_DISTANCE;
}

int DefaultSettings::getAlturaMenuInferior(){
	return ALTURA_MENU_INFERIOR;
}

int DefaultSettings::getAlturaMenuSuperior(){
	return ALTURA_MENU_SUPERIOR;
}

int DefaultSettings::getAlturaBandaMenu(){
	return ALTURA_BANDA_MENU;
}

string DefaultSettings::getPathOfFoggedTile() {
	return IMAGE_BASE_PATH +"/Tiles/" + PATH_OF_FOGGED_TILE + ".png";
}

string DefaultSettings::getPathOfCoveredTile() {
	return IMAGE_BASE_PATH +"/Tiles/" + PATH_OF_COVERED_TILE + ".png";
}

int DefaultSettings::getRangeVisibility() {
	return RANGE_VISIBILITY;
}

string DefaultSettings::getPathOfMenuBackground(){
	return PATH_MENU_BACKGROUND;
}

map<string,int> DefaultSettings::getCostsOf(string type) {
	map<string,int>  returnMap;
	if (type == "soldado") {
		returnMap["food"] = 3;
		returnMap["gold"] = 2;
	}else if (type == "aldeano") {
		returnMap["food"] = 3;
		returnMap["rock"] = 2;
	}else if (type == "Castle") {
		returnMap["food"] = 10;
		returnMap["rock"] = 10;
		returnMap["gold"] = 10;
	}else if (type == "Army"){
		returnMap["food"] = 8;
		returnMap["rock"] = 8;
		returnMap["gold"] = 8;
		returnMap["wood"] = 8;
	}else if (type == "molino"){
		returnMap["food"] = 5;
		returnMap["rock"] = 5;
		returnMap["gold"] = 5;
		returnMap["wood"] = 5;
	}else if (type == "cobra"){
		returnMap["food"] = 1000;
		returnMap["rock"] = 1000;
		returnMap["gold"] = 1000;
		returnMap["wood"] = 1000;
	}else if (type == "caballo"){
		returnMap["food"] = 100;
		returnMap["rock"] = 100;
		returnMap["gold"] = 100;
		returnMap["wood"] = 100;
	}
	return returnMap;
}
string DefaultSettings::getPathFlagImage(string stringColor){
	if(stringColor==""){
		stringColor="flag";
	}
	return IMAGE_BASE_PATH +"/Flags/" + stringColor + ".png";
}

string DefaultSettings::getPathTileColour(string stringColor){
	if(stringColor==""){
		stringColor = "grey";
	}
	return IMAGE_BASE_PATH +"/Tiles/" + stringColor + "Tile.png";
}

string DefaultSettings::getPathTileAvailable(bool available){
	if(available)
		return IMAGE_BASE_PATH +"/Tiles/lightGreenTile.png";
	return IMAGE_BASE_PATH +"/Tiles/redTile.png";
}

string DefaultSettings::covertPathOfAnimatedEntity(string path){
	size_t found = path.find("Molino");
	if(found!=string::npos) path=path.replace(path.find("Molino"), sizeof("Molino")-1, "MolinoSolo");
	found = path.find("soldado.");
	if(found!=string::npos) path=path.replace(path.find("soldado."), sizeof("soldado.")-1, "soldadoSolo.");
	found = path.find("king");
	if(found!=string::npos) path=path.replace(path.find("king"), sizeof("king")-1, "kingSolo");
	found = path.find("aldeano");
	if(found!=string::npos) path=path.replace(path.find("aldeano"), sizeof("aldeano")-1, "aldeanoSolo");
	found = path.find("cobra");
	if(found!=string::npos) path=path.replace(path.find("cobra"), sizeof("cobra")-1, "cobraSolo");
	found = path.find("caballo");
	if(found!=string::npos) path=path.replace(path.find("caballo"), sizeof("caballo")-1, "caballoSolo");
	found = path.find("soldadoDesconectado");
	if(found!=string::npos) path=path.replace(path.find("soldadoDesconectado"), sizeof("soldado.")-1, "soldadoSolo");
	return path;
}

DefaultSettings::~DefaultSettings() {
}
