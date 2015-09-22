/*
 * GameSettings.h
 *
 *  Created on: 19/9/2015
 *      Author: nico
 */

#ifndef GAMESETTINGS_H_
#define GAMESETTINGS_H_

#include "Loader.h"
#include "DefaultSettings.h"
#include "EntidadEstatica.h"
#include <list>
#include <fstream>

namespace std {

class GameSettings {
private:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int TILE_SIZE;
	int CONF_VEL_PERSONAJE;
	int LONG_MARGEN_SCROLL;
	string NOMBRE_ESCENARIO;
	string IMAGE_BASE_PATH;
	string AGE_OF_EMPIRES;
	string IMAGE_TILES_PATH;
	string IMAGE_PERSONAJES_PATH;
	int MAP_WIDTH;
	int MAP_HEIGHT;
	int MEDIUM_SIZE;
	int VELOCIDAD_SCROLL_UNO;
	int VELOCIDAD_SCROLL_DOS;
	Loader* loader;
	static GameSettings* instance;
	GameSettings();
	bool isFileExist(const string fileName);
	void processTypes();


public:
	list<EntidadEstatica*> edificios;
	void SetGameSettings();
	static GameSettings* GetInstance();
	virtual ~GameSettings();
	int getScreenWidth();
	int getScreenHeight();
	int getTileSize();
	int getLongMargenScroll();
	string getNombreEscenario();
	int getMapWidth();
	int getMapHeight();
	int getMediumSize();
	string getAgeOfEmpires();
	string imagePathBuildingsByTypeAndAge(const string &object,const string &age);
	string imagePathPersonajesByType(const string &object);
	string imagePathTilesByType(const string &object);

	string defaultImage();
	bool isEntityTypeValid(const string &type);
	int getVelocidadScrollUno();
	int getVelocidadScrollDos();
	int getLimiteDerecho();
	int getLimiteIzquierdo();
	int getLimiteInferior();
	int getLimiteSuperior();
	int getMargenDerechoUno();
	int getMargenDerechoDos();
	int getMargenIzquierdoUno();
	int getMargenIzquierdoDos();
	int getMargenSuperiorUno();
	int getMargenSuperiorDos();
	int getMargenInferiorUno();
	int getMargenInferiorDos();
	void createEntidades();
	string getValueInMap(map<string,string> myMap, const string &key);
	map<string,string> getValueInVector(vector < map<string,string> > myVector, const string &key, const string &value);
	list<EntidadEstatica*> getEntidadesEstaticas();

};

} /* namespace std */

#endif /* GAMESETTINGS_H_ */
