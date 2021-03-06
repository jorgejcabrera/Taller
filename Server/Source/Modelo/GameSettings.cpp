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
	this->loader = new Loader();
	this->loader->load();
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

int GameSettings::getMapWidth(){
	return (MAP_WIDTH > 0 ) ? MAP_WIDTH : DefaultSettings::getMapWidth();
}

int GameSettings::getMapHeight(){
	return (MAP_HEIGHT > 0 ) ? MAP_HEIGHT : DefaultSettings::getMapHeight();
}

string GameSettings::imagePathBuildingsByTypeAndAge(const string &object,const string &age){
	return DefaultSettings::imagePathBuildingsByTypeAndAge(object,age);
}

string GameSettings::imagePathPersonajesByType(const string &object){
	return DefaultSettings::imagePathPersonajesByType(object);
}

string GameSettings::imagePathTilesByType(const string &object){
	return DefaultSettings::imagePathTilesByType(object);
}

void GameSettings::createConfMessages(){
	vector< map< string, string> > *listaDeTipos = loader->getTypes();
	for(vector< map< string, string> >::iterator it=listaDeTipos->begin(); it!=listaDeTipos->end(); ++it){
		string name = getValueInMap(*it, "nombre");
		string path = getValueInMap(*it, "imagen");
		int anchoBase =  atoi(getValueInMap(*it, "ancho_base").c_str());
		int altoBase = atoi(getValueInMap(*it, "alto_base").c_str());
		int fps = atoi(getValueInMap(*it, "fps").c_str());
		int delay = atoi(getValueInMap(*it, "delay").c_str());
		int total_frames_line = atoi(getValueInMap(*it, "total_frames_line").c_str());
		int pixels_dimension = atoi(getValueInMap(*it, "pixels_dimension").c_str());

		Message* newMessage = new Message(0,"config");
		newMessage->setName(name);
		newMessage->setImagePath(path);
		newMessage->setBaseWidth(anchoBase);
		newMessage->setBaseHeight(altoBase);
		newMessage->setFps(fps);
		newMessage->setDelay(delay);
		newMessage->setTotalFramesLine(total_frames_line);
		newMessage->setPixelsDimension(pixels_dimension);

		this->messageConfigList.push_back(newMessage);
	}
}

list<Message*> GameSettings::getConfMessages(){
	return this->messageConfigList;
}

Message* GameSettings::getWindowMessage(){
	Message* msgWindow = new Message(0,"window");
	msgWindow->setName("window");
	msgWindow->setPosition(make_pair(this->getScreenWidth(),this->getScreenHeight()));
	msgWindow->setBaseWidth(this->getMapWidth());
	msgWindow->setBaseHeight(this->getMapHeight());
	return msgWindow;
}

void GameSettings::SetGameSettings(){
	map<string,int>* mapSI;
	map< string, string> * mapSS;

	// seteo screen
	mapSI = loader->getScreen();
	this->SCREEN_HEIGHT = mapSI->operator []("alto");
	this->SCREEN_WIDTH = mapSI->operator []("ancho");
	mapSI->clear();
	// seteo conf
	mapSI = loader->getConf();
	this->LONG_MARGEN_SCROLL = mapSI->operator []("margen_scroll");
	mapSI->clear();
	//seteo escenario
	mapSS = loader->getStage();
	this->NOMBRE_ESCENARIO = mapSS->operator []("orleans");
	this->MAP_HEIGHT = atoi(mapSS->operator []("size_x").c_str());
	this->MAP_WIDTH = atoi(mapSS->operator []("size_y").c_str());
	mapSS->clear();

	// los pongo en NULL para no borrar informacion del Loader
	mapSI = NULL;
	mapSS = NULL;
	delete mapSI;
	delete mapSS;
}

GameSettings* GameSettings::GetInstance() {
	if (!instance) {
		instance = new GameSettings();
		instance->SetGameSettings();
		//instance->createEntidades();
		instance->createConfMessages();
	}
	return instance;
}

/*void GameSettings::createEntidades(){
	vector< map< string, string> > *entidades = loader->getEntitys();
	for(vector< map< string, string> >::iterator it = entidades->begin(); it!= entidades->end(); ++it){
			string nombre = this->getValueInMap(*it, "tipo");
			string posXStr = this->getValueInMap(*it, "x");
			string posYStr = this->getValueInMap(*it, "y");
			int posX = atoi(posXStr.c_str());
			int posY = atoi(posYStr.c_str());

			if(nombre!="" and posXStr!= "" and posYStr!="" and posX<this->MAP_WIDTH and posY<this->MAP_HEIGHT){
				map<string,string> entidadObjeto = this->getValueInVector(*(loader->getTypes()), "nombre", nombre);
				string tipoEntidad = DefaultSettings::getTypeEntity(nombre);
				if((tipoEntidad == "edificios") or (tipoEntidad=="semiestaticos")){
					int anchoBase = atoi(this->getValueInMap(entidadObjeto, "ancho_base").c_str());
					int altoBase = atoi(this->getValueInMap(entidadObjeto, "alto_base").c_str());
					if(anchoBase>0 and altoBase>0){
						if(tipoEntidad == "edificios"){
							EntidadEstatica* edificioCreado = new EntidadEstatica(nombre,anchoBase,altoBase,true);
							edificioCreado->setPosition(posX,posY);
							this->edificios.push_back(edificioCreado);
						}else if (tipoEntidad=="semiestaticos"){
							int fps = atoi(this->getValueInMap(entidadObjeto, "fps").c_str());
							int delay = atoi(this->getValueInMap(entidadObjeto, "delay").c_str());
							int total_frames_line = atoi(this->getValueInMap(entidadObjeto, "total_frames_line").c_str());
							int total_frames = (total_frames_line > 0) ? total_frames_line : 1;
							if(fps > 50) fps = 50;
							EntidadSemiEstatica* molino = new EntidadSemiEstatica(nombre, anchoBase,altoBase,150,150,fps);
							molino->setPosition(posX,posY);
							molino->setDelay(delay);
							molino->setFramesInLineFile(total_frames);
							molino->setHealth(1000);
							this->edificios.push_back(molino);
						}
					}
				}else if (tipoEntidad=="tiles" && posX < this->getMapHeight() && posY < this->getMapHeight()){
					this->tiles.insert(make_pair(make_pair(posX,posY),nombre));
				}
			}
	}
}*/

string GameSettings::getConfigAttributeOfEntityAsString(string nombre, string attribute){
	map<string,string> entidadObjeto = this->getValueInVector(*(loader->getTypes()), "nombre", nombre);
	return this->getValueInMap(entidadObjeto, attribute);
}

int GameSettings::getConfigAttributeOfEntityAsInt(string nombre, string attribute){
	map<string,string> entidadObjeto = this->getValueInVector(*(loader->getTypes()), "nombre", nombre);
	return atoi(this->getValueInMap(entidadObjeto, attribute).c_str());
}


list<EntidadPartida*> GameSettings::getEntidadesEstaticas(){
	return this->edificios;
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
	//TODO: borrar la lista de mensajes de configuracion

	delete(this->loader);
	this->loader = NULL;
	this->instance =NULL;
}

int GameSettings::getRangeVisibility() {
	return DefaultSettings::getRangeVisibility(); // TODO que cada entidad tenga su propia visibilidad, y que esto se obtenga del yaml
}

} /* namespace std */
