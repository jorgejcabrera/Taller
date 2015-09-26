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
	this->SCREEN_HEIGHT = mapSI->operator []("alto");
	this->SCREEN_WIDTH = mapSI->operator []("ancho");
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

	map<string,string> entidadObjeto = this->getValueInVector(*(loader->getTypes()), "nombre", this->TIPO_PROTAGONISTA);
	int fps = atoi(this->getValueInMap(entidadObjeto, "fps").c_str());
	if(fps>0){
		this->FPS_PROTAGONISTA = fps;
	}else{
		this->FPS_PROTAGONISTA = 1;
	}

	string imagen = this->getValueInMap(entidadObjeto, "imagen");
	if(!(isFileExist(imagen))){
		cout << "LOG.INFO : Uso la imagen por deafult porque no exite el file: " << imagen <<endl;
		this->PATH_PROTAGONISTA = DefaultSettings::defaultImage();
	}else{
		this->PATH_PROTAGONISTA = imagen;
	}

	int total_frames_line = atoi(this->getValueInMap(entidadObjeto, "total_frames_line").c_str());
	if(total_frames_line>0){
		this->FRAMES_IN_FILE_PROTAGONISTA = total_frames_line;
	}else{
		this->FRAMES_IN_FILE_PROTAGONISTA = 7;
	}

	int pixels_dimension = atoi(this->getValueInMap(entidadObjeto, "pixels_dimension").c_str());
	if(pixels_dimension>0){
		this->PIXEL_DIMENSION_PROTAGONISTA = pixels_dimension;
	}else{
		this->PIXEL_DIMENSION_PROTAGONISTA = 50;
	}

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
		instance->createEntidades();
	}
	return instance;
}

GameSettings::~GameSettings() {
	for (list<EntidadPartida*>::iterator it=this->edificios.begin(); it!=this->edificios.end(); ++it){
			(*it)->~EntidadPartida();
		//(*it)=NULL;
		}
	for (map<pair<int,int>,string>::iterator it=this->tiles.begin(); it!=this->tiles.end(); ++it){
		this->tiles.erase(it);
	}
	//this->edificios = NULL;
	this->loader->~Loader();
	this->loader = NULL;
	this->instance =NULL;
}

//TODO: borrar este metodo
void GameSettings::processTypes(){
	/*vector< map< string, string> > *tipos = loader->getTypes();

	for(vector< map< string, string> >::iterator it = tipos->begin(); it!= tipos->end(); ++it){
		for (std::map<string,string>::iterator itMap=it->begin(); itMap!=it->end(); ++itMap)
		    std::cout << itMap->first << " => " << itMap->second << '\n';
	}*/
}

void GameSettings::createEntidades(){
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
				string imagen = this->getValueInMap(entidadObjeto, "imagen");
				if(!(isFileExist(imagen))){
					cout << "LOG.INFO : Uso la imagen por deafult porque no exite el file: " << imagen <<endl;
					imagen = DefaultSettings::defaultImage();
				}
				if((tipoEntidad == "edificios") or (tipoEntidad=="semiestaticos")){
					int anchoBase = atoi(this->getValueInMap(entidadObjeto, "ancho_base").c_str());
					int altoBase = atoi(this->getValueInMap(entidadObjeto, "alto_base").c_str());
					if(anchoBase>0 and altoBase>0){
						if(tipoEntidad == "edificios"){
							EntidadEstatica* edificioCreado = new EntidadEstatica(anchoBase,altoBase,nombre,true,imagen);
							edificioCreado->setPosition(posX,posY);
							this->edificios.push_back(edificioCreado);
						}else if (tipoEntidad=="semiestaticos"){
							int fps = atoi(this->getValueInMap(entidadObjeto, "fps").c_str());
							int delay = atoi(this->getValueInMap(entidadObjeto, "delay").c_str());
							int total_frames_line = atoi(this->getValueInMap(entidadObjeto, "total_frames_line").c_str());
							int total_frames = (total_frames_line > 0) ? total_frames_line : 1;
							if(fps > 50) fps = 50;
							EntidadSemiEstatica* molino = new EntidadSemiEstatica(anchoBase,altoBase,150,150,fps,nombre,imagen);
							molino->setPosition(posX,posY);
							molino->setDelay(delay);
							molino->setFramesInLineFile(total_frames);
							this->edificios.push_back(molino);
						}
					}
				}else if (tipoEntidad=="tiles" && posX < this->getMapHeight() && posY < this->getMapHeight()){
					this->tiles.insert(make_pair(make_pair(posX,posY),imagen));
				}
			}
	}
}

int GameSettings::getProtagonistaFPS(){
	return this->FPS_PROTAGONISTA;
}

string GameSettings::getProtagonistaPath(){
	return this->PATH_PROTAGONISTA;
}

int GameSettings::getProtagonistaFramesInFile(){
	return this->FRAMES_IN_FILE_PROTAGONISTA;
}

int GameSettings::getProtagonistaPixelDimension(){
	return this->PIXEL_DIMENSION_PROTAGONISTA;
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

} /* namespace std */
