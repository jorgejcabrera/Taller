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
#include <vector>

namespace std {

class Loader {
private:
	map<string,int>* screen;
	map<string,int>* conf;
	vector< map< string, string> >* type;
	map< string, string> * stage;
	vector< map< string, string> >* entitys;
	map< string, string> * mainCharacter;


//	map<void,void>* stage;

/*	int SCREEN_WIDTH;
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
*/	Loader();
	static Loader* instance;
	void load();

public:

	static Loader* GetInstance();
	int getScreenWidth();
	int getScreenHeight();
	vector< map< string, string> >* getTypes();
	vector< map< string, string> >* getEntitys();
	map<string,int>* getConf();
	map< string, string> * getStage();
	map< string, string> * getMainCharacter();
/*	int getMargenScroll();
	int getVelPersonaje();
	int getTileSize();
	string getNombreEscenario();
	int getMapWidth();
	int getMapHeight();
	int getMediumSize();
	string getAgeOfEmpires();
	string imagePathByTypeAndAge(const string &object,const string &age);
	string defaultImage();
	bool isEntityTypeValid(const string &type);
*/	virtual ~Loader();
};

} /* namespace std */

#endif /* LOADER_H_ */
