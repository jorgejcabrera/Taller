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
#include "EntidadPartida.h"
#include "EntidadEstatica.h"
#include "EntidadSemiEstatica.h"
#include "../Utils/Socket/Message.h"
#include <list>
#include <fstream>
#include <map>

namespace std {

class GameSettings {
private:

	Loader* loader;
	static GameSettings* instance;
	GameSettings();
	bool isFileExist(const string fileName);

public:
	list<Message*> messageConfigList;
	//pantalla:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	//configuracion:
	int VELOCIDAD_PERSONAJE;
	int LONG_MARGEN_SCROLL;
	//escenario
	string NOMBRE_ESCENARIO;
	int MAP_WIDTH;
	int MAP_HEIGHT;
	//protagonista
	string TIPO_PROTAGONISTA;
	int POS_X_PROTAGONISTA;
	int POS_Y_PROTAGONISTA;
	//tipos
	//vector< map< string, string> >* tipos;
	//entidades
	//vector< map< string, string> >* entidades;

	int TILE_SIZE;
	int CONF_VEL_PERSONAJE;
	string IMAGE_BASE_PATH;
	string AGE_OF_EMPIRES;
	string IMAGE_TILES_PATH;
	string IMAGE_PERSONAJES_PATH;
	int MEDIUM_SIZE;

	int FPS_PROTAGONISTA;
	string PATH_PROTAGONISTA;
	int FRAMES_IN_FILE_PROTAGONISTA;
	int PIXEL_DIMENSION_PROTAGONISTA;
	int DELAY_PROTAGONISTA;

	list<EntidadPartida*> edificios;
	map<pair<int,int>,string> tiles;
	void SetGameSettings();
	static GameSettings* GetInstance();
	virtual ~GameSettings();
	int getScreenWidth();
	int getScreenHeight();
	int getTileSize();
	string getNombreEscenario();
	int getMapWidth();
	int getMapHeight();
	int getMediumSize();
	string imagePathBuildingsByTypeAndAge(const string &object,const string &age);
	string imagePathPersonajesByType(const string &object);
	string imagePathTilesByType(const string &object);

	string defaultImage();
	bool isEntityTypeValid(const string &type);
	void createEntidades();
	string getValueInMap(map<string,string> myMap, const string &key);
	map<string,string> getValueInVector(vector < map<string,string> > myVector, const string &key, const string &value);
	list<EntidadPartida*> getEntidadesEstaticas();
	string getTipoProtagonista();
	int getPosXProtagonista();
	int getPosYProtagonista();
	int getVelocidadPersonaje();
	map<pair<int,int>,string> getTiles();
	int getProtagonistaFPS();
	string getProtagonistaPath();
	int getProtagonistaFramesInFile();
	int getProtagonistaPixelDimension();
	int getProtagonistaDelay();

	void generateListMessageConfiguration();
	list<Message*> getListMessageConfiguration();
	int getRangeVisibility();

	/*
	 * devuelve el ancho y el alto para un tipo dado
	 */
	pair<int,int> getConfigDimensionOfEntity(string nombre);
	/*
	 * Dado un tipo y un parametro devuelve el valor
	 */
	int getValueForAttributeOfEntity(string nombre, string attribute);
};

} /* namespace std */

#endif /* GAMESETTINGS_H_ */
