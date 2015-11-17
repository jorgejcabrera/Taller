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
	int LONG_MARGEN_SCROLL;
	//escenario
	string NOMBRE_ESCENARIO;
	int MAP_WIDTH;
	int MAP_HEIGHT;

	list<EntidadPartida*> edificios;
	map<pair<int,int>,string> tiles;
	static GameSettings* GetInstance();
	void SetGameSettings();
	int getScreenWidth();
	int getScreenHeight();
	int getTileSize();
	int getMapWidth();
	int getMapHeight();
	int getRangeVisibility();
	list<Message*> getConfMessages();
	Message* getWindowMessage();
	map<pair<int,int>,string> getTiles();
	string imagePathBuildingsByTypeAndAge(const string &object,const string &age);
	string imagePathPersonajesByType(const string &object);
	string imagePathTilesByType(const string &object);
	string getValueInMap(map<string,string> myMap, const string &key);
	map<string,string> getValueInVector(vector < map<string,string> > myVector, const string &key, const string &value);
	list<EntidadPartida*> getEntidadesEstaticas();
	void createConfMessages();
	/*
	 * Devuelve un string con el valor del atributo de configuracion seteado en el yaml para la entidad
	 */
	string getConfigAttributeOfEntityAsString(string nombre, string attribute);
	/*
	* Devuelve un int con el valor del atributo de configuracion seteado en el yaml para la entidad
	* */
	int getConfigAttributeOfEntityAsInt(string nombre, string attribute);
	virtual ~GameSettings();
};

} /* namespace std */

#endif /* GAMESETTINGS_H_ */
