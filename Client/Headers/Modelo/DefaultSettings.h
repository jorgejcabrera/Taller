/*
 * Constantes.h
 *
 *  Created on: 2 de set. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_DEFAULTSETTINGS_H_
#define SOURCE_MODELO_DEFAULTSETTINGS_H_

#include <string>
#include <list>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <map>

using namespace std;

class DefaultSettings {
	private:
		static const int SCREEN_WIDTH = 800;
		static const int SCREEN_HEIGHT = 600;
		static const int TILE_SIZE = 40;
		static const int LONG_MARGEN_SCROLL = 30;
		static const string NOMBRE_ESCENARIO;
		static const string IMAGE_BASE_PATH;
		static const string AGE_OF_EMPIRES;
		static const string IMAGE_TILES_PATH;
		static const string IMAGE_PERSONAJES_PATH;
		static const int MAP_WIDTH = 20;							//esto vendría a ser el eje x
		static const int MAP_HEIGHT = 20 ;							//esto viene a ser el eje y
		static const int MEDIUM_SIZE = 3;
		static const int VELOCIDAD_SCROLL_UNO = 10;
		static const int VELOCIDAD_SCROLL_DOS = 30;
		static const int TIMEOUT = 10;
		static const int ALTURA_MENU_INFERIOR= 120;
		static const int ALTURA_MENU_SUPERIOR= 20;
		static const int ALTURA_BANDA_MENU= 10;
		static const int VIEW_DISTANCE = 4;
		static const string PATH_OF_FOGGED_TILE;
		static const string PATH_OF_COVERED_TILE;
		static const int RANGE_VISIBILITY = 4;
		static const string PATH_MENU_BACKGROUND;
		static const int FOOD_OF_NEW_SOLDIER = 3;
		static const int ROCK_OF_NEW_SOLDIER = 2;

	public:
		DefaultSettings();
		virtual ~DefaultSettings();
		static int getScreenWidth();
		static int getScreenHeight();
		static int getTileSize();
		static int getLongMargenScroll();
		static string getNombreEscenario();
		static int getMapWidth();
		static int getMapHeight();
		static int getMediumSize();
		static string getAgeOfEmpires();
		static string imagePathBuildingsByTypeAndAge(const string &object,const string &age);
		static string imagePathPersonajesByType(const string &object);
		static string imagePathTilesByType(const string &object);

		static string defaultImage();
		static bool isEntityTypeValid(const string &type);
		static int getVelocidadScrollUno();
		static int getVelocidadScrollDos();
		static int getLimiteDerecho();
		static int getLimiteIzquierdo();
		static int getLimiteInferior();
		static int getLimiteSuperior();
		static int getMargenDerechoUno();
		static int getMargenDerechoDos();
		static int getMargenIzquierdoUno();
		static int getMargenIzquierdoDos();
		static int getMargenSuperiorUno();
		static int getMargenSuperiorDos();
		static int getMargenInferiorUno();
		static int getMargenInferiorDos();
		static string getTypeEntity(const string &type);
		static bool isInList(list<string> listOfThings, const string &type);
		static list<string> getListOfAttributesCanSetByType(const string &type);
		static int getTimeOut();
		static int getViewDistance();
		static int getAlturaMenuInferior();
		static int getAlturaMenuSuperior();
		static int getAlturaBandaMenu();
		static string getPathOfFoggedTile();
		static string getPathOfCoveredTile();
		static int getRangeVisibility();
		static string getPathOfMenuBackground();
		static map<string,int> getCostsOf(string type);
		static string getPathFlagImage(string stringColor);
		static string getPathTileColour(string stringColor);
		static string getPathTileAvailable(bool available);
};


#endif /* SOURCE_MODELO_DEFAULTSETTINGS_H_ */
