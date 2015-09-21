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

namespace std {

class GameSettings {
private:
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
	vector< map< string, string> >* tipos;
	//entidades
	vector< map< string, string> >* entidades;


	int TILE_SIZE;
	int CONF_VEL_PERSONAJE;
	string IMAGE_BASE_PATH;
	string AGE_OF_EMPIRES;
	string IMAGE_TILES_PATH;
	string IMAGE_PERSONAJES_PATH;
	int MEDIUM_SIZE;
	int VELOCIDAD_SCROLL_UNO;
	int VELOCIDAD_SCROLL_DOS;
	Loader* loader;
	static GameSettings* instance;


public:
	GameSettings();
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
	string getTipoProtagonista();
	int getPosXProtagonista();
	int getPosYProtagonista();
	int getVelocidadPersonaje();
};

} /* namespace std */

#endif /* GAMESETTINGS_H_ */
