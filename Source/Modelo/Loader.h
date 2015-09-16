/*
 * Loader.h
 *
 *  Created on: 12/9/2015
 *      Author: nico
 */

#ifndef LOADER_H_
#define LOADER_H_

#include <yaml.h>
#include "DefaultSettings.h"
#include <iostream>
#include <map>
#include <string>

namespace std {

class Loader {
private:
	map<string,int>* screen;
	map<string,int>* conf;
//	list<map<void,void> >* type;
//	map<void,void>* stage;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int TILE_SIZE;
	int CONF_VEL_PERSONAJE;
	int MARGEN_SCROLL;
	string NOMBRE_ESCENARIO;
	string IMAGE_BASE_PATH;
	string AGE_OF_EMPIRES;
	int MAP_WIDTH;							//esto vendría a ser el eje x
	int MAP_HEIGHT;							//esto viene a ser el eje y
	int MEDIUM_SIZE;

public:
	Loader();
	void Load();
	int getScreenWidth();
	int getScreenHeight();
	int getTileSize();
	int getMargenScroll();
	string getNombreEscenario();
	int getMapWidth();
	int getMapHeight();
	int getMediumSize();
	string getAgeOfEmpires();
	string imagePathByTypeAndAge(const string &object,const string &age);
	string defaultImage();
	bool isEntityTypeValid(const string &type);
	virtual ~Loader();
};

} /* namespace std */

#endif /* LOADER_H_ */
