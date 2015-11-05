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
	//TODO: esto deberia estar solo en la vista
	if((SCREEN_WIDTH<=0) or (SCREEN_WIDTH>DefaultSettings::getScreenWidth()))
		return DefaultSettings::getScreenWidth();
	return this->SCREEN_WIDTH;
}

int GameSettings::getScreenHeight(){
	//TODO: esto deberia estar solo en la vista
	if((SCREEN_HEIGHT<=0) or (SCREEN_HEIGHT>DefaultSettings::getScreenHeight()))
		return DefaultSettings::getScreenHeight();
	return this->SCREEN_HEIGHT;
}

int GameSettings::getTileSize(){
	return DefaultSettings::getTileSize();
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

void GameSettings::generateListMessageConfiguration(){
	//Genero una lista de mensajes de configuracion para mandarle a cada cliente
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
		this->messageConfigList.push_back(new Message(name,path,anchoBase,altoBase,fps,delay,total_frames_line,pixels_dimension));
	}
}

list<Message*> GameSettings::getListMessageConfiguration(){
	return this->messageConfigList;
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

	int delay = atoi(this->getValueInMap(entidadObjeto, "delay").c_str());
	this->DELAY_PROTAGONISTA = delay;

	string imagen = this->getValueInMap(entidadObjeto, "imagen");
	if(!(isFileExist(imagen))){
		cout << "LOG.INFO : Uso la imagen por default porque no existe el file: " << imagen <<endl;
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
		instance->generateListMessageConfiguration();
	}
	return instance;
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
				//TODO: este es un control que debe hacer el cliente
				/*string imagen = this->getValueInMap(entidadObjeto, "imagen");
				if(!(isFileExist(imagen))){
					cout << "LOG.INFO : Uso la imagen por deafult porque no exite el file: " << imagen <<endl;
					imagen = DefaultSettings::defaultImage();
				}*/
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
							this->edificios.push_back(molino);
						}
					}
				}else if (tipoEntidad=="tiles" && posX < this->getMapHeight() && posY < this->getMapHeight()){
					//TODO: modifico lo que hay en la cola, ahora solo guardo que tipo de tile es, antes mandaba el path. Eso deberia resolverlo la vista
					this->tiles.insert(make_pair(make_pair(posX,posY),nombre));
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

int GameSettings::getProtagonistaDelay(){
	return this->DELAY_PROTAGONISTA;
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
