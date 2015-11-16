/*
 * GameSettings.h
 *
 *  Created on: 19/9/2015
 *      Author: nico
 */

#ifndef GAMESETTINGS_H_
#define GAMESETTINGS_H_

#include "DefaultSettings.h"
#include <list>
#include <fstream>
#include <map>
#include <vector>
#include "../../Headers/Vista/EntidadEstaticaVista.h"
#include "../../Headers/Vista/EntidadPartidaVista.h"
#include "../../Headers/Vista/EntidadSemiEstaticaVista.h"
#include "EntidadConfig.h"

namespace std {

class GameSettings {
private:
	static GameSettings* instance;
	GameSettings();
	bool isFileExist(const string fileName);
	map<string,EntidadConfig*> entitiesConfig;

public:
	//pantalla:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	//configuracion:
	int VELOCIDAD_PERSONAJE;
	int LONG_MARGEN_SCROLL=30;
	//escenario
	string NOMBRE_ESCENARIO;
	int MAP_WIDTH=30;
	int MAP_HEIGHT=30;

	int TILE_SIZE;
	string IMAGE_BASE_PATH;
	string AGE_OF_EMPIRES;
	string IMAGE_TILES_PATH;
	string IMAGE_PERSONAJES_PATH;
	int MEDIUM_SIZE;
	int VELOCIDAD_SCROLL_UNO;
	int VELOCIDAD_SCROLL_DOS;

	list<EntidadPartidaVista*> edificios;
	map<pair<int,int>,string> tiles;
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
	string getValueInMap(map<string,string> myMap, const string &key);
	map<string,string> getValueInVector(vector < map<string,string> > myVector, const string &key, const string &value);
	list<EntidadPartidaVista*> getEntidadesEstaticas();
	map<pair<int,int>,string> getTiles();
	int getAlturaMenuInferior();

	//AGREGADO EN CLIENTE UNICAMENTE
	void setScreenDimension(int width, int heigth);
	void addEntityConfig(EntidadConfig* entity);
	EntidadConfig* getEntityConfig(string nameEntity);
	void setMapDimention(int ancho, int alto);
	string getPathOfFoggedTile();
	string getPathOfCoveredTile();
	int getRangeVisibility();
	map<string,int> getCostsOf(string type);
};

} /* namespace std */

#endif /* GAMESETTINGS_H_ */
