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
	loader->load();

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

string GameSettings::getTipoProtagonista(){
	return (TIPO_PROTAGONISTA != "") ? TIPO_PROTAGONISTA : DefaultSettings::getTipoProtagonista();
}

int GameSettings::getPosXProtagonista(){
	return (this->POS_X_PROTAGONISTA > 0) ? this->POS_X_PROTAGONISTA : DefaultSettings::getPosXProtagonista();
}
int GameSettings::getPosYProtagonista(){
	return (this->POS_Y_PROTAGONISTA > 0) ? this->POS_Y_PROTAGONISTA : DefaultSettings::getPosYProtagonista();
}

int GameSettings::getVelocidadPersonaje	(){
	return (this->VELOCIDAD_PERSONAJE > 0) ? this->VELOCIDAD_PERSONAJE: DefaultSettings::getVelocidadPersonaje();
}

void GameSettings::SetGameSettings(){
	map<string,int>* mapSI = new map<string,int>();
	map< string, string> * mapSS = new map< string, string>();

	// seteo screen
	mapSI = loader->getScreen();
	this->SCREEN_HEIGHT = mapSI->operator []("ancho");
	this->SCREEN_WIDTH = mapSI->operator []("alto");
	mapSI->clear();
	// seteo conf
	mapSI = loader->getConf();
	this->VELOCIDAD_PERSONAJE = mapSI->operator []("vel_personaje");
	this->LONG_MARGEN_SCROLL = mapSI->operator []("margen_scroll");
	mapSI->clear();
	//seteo escenario
	mapSS = loader->getStage();
	this->NOMBRE_ESCENARIO = mapSS->operator []("orleans");
	this->MAP_HEIGHT = atoi(mapSS->operator []("size_x").c_str());
	this->MAP_WIDTH = atoi(mapSS->operator []("size_y").c_str());
	mapSS->clear();
	//seteo protagonista
	mapSS = loader->getMainCharacter();
	this->TIPO_PROTAGONISTA = mapSS->operator []("tipo");
	this->POS_X_PROTAGONISTA = atoi(mapSS->operator []("x").c_str());
	this->POS_Y_PROTAGONISTA = atoi(mapSS->operator []("y").c_str());
	mapSS->clear();
	//seteo entidades
	//this->entidades = loader->getEntitys();
	//seteo tipos
	//this->tipos = loader->getTypes();

}

GameSettings* GameSettings::GetInstance() {
	if (!instance) {
		instance = new GameSettings();
		instance->SetGameSettings();
		instance->createEntidades();
	}
	return instance;
}

GameSettings::~GameSettings() {
	for (list<EntidadEstatica*>::iterator it=this->edificios.begin(); it!=this->edificios.end(); ++it){
			(*it)->~EntidadEstatica();
		}
	//this->edificios = NULL;
	this->instance =NULL;
}

//TODO: revisar este metodo
void GameSettings::processTypes(){
	vector< map< string, string> > *tipos = loader->getTypes();

	for(vector< map< string, string> >::iterator it = tipos->begin(); it!= tipos->end(); ++it){
		cout <<"ENTRE en processTypes"<<endl;
		for (std::map<string,string>::iterator itMap=it->begin(); itMap!=it->end(); ++itMap)
		    std::cout << itMap->first << " => " << itMap->second << '\n';
	}
}

void GameSettings::createEntidades(){
	vector< map< string, string> > *entidades = loader->getEntitys();
	for(vector< map< string, string> >::iterator it = entidades->begin(); it!= entidades->end(); ++it){
			string nombre = this->getValueInMap(*it, "tipo");//  getValueInMap(it,"nombre");
			string posXStr = this->getValueInMap(*it, "x");
			string posYStr = this->getValueInMap(*it, "y");
			int posX = atoi(posXStr.c_str());
			int posY = atoi(posYStr.c_str());

			if(nombre!="" and posXStr!= "" and posYStr!="" and posX<=this->MAP_WIDTH and posY<=this->MAP_HEIGHT){
				map<string,string> entidadObjeto = this->getValueInVector(*(loader->getTypes()), "nombre", nombre);
				string tipoEntidad = DefaultSettings::getTypeEntity(nombre);
				string imagen = this->getValueInMap(entidadObjeto, "imagen");
				if(tipoEntidad == "edificios"){
					int anchoBase = atoi(this->getValueInMap(entidadObjeto, "ancho_base").c_str());
					int altoBase = atoi(this->getValueInMap(entidadObjeto, "alto_base").c_str());
					if(anchoBase>0 and altoBase>0){
						EntidadEstatica* edificioCreado = new EntidadEstatica(anchoBase,altoBase,nombre,true,imagen);
						edificioCreado->setPosition(posX,posY);
						this->edificios.push_back(edificioCreado);
					}
				}
			}


			//list<string> lista = DefaultSettings::getListOfAttributesCanSetByType(tipoEntidad);
			//for (std::map<string,string>::iterator itMap=entidadObjeto.begin(); itMap!=entidadObjeto.end(); ++itMap)
			  //std::cout << itMap->first << " => " << itMap->second << '\n';
	}
}

list<EntidadEstatica*> GameSettings::getEntidadesEstaticas(){
	return this->edificios;
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

} /* namespace std */
