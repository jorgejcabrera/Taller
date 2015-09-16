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

using namespace std;

class DefaultSettings {
	private:
		static const int SCREEN_WIDTH = 1024;
		//static const int SCREEN_HEIGHT = 860;
		static const int SCREEN_HEIGHT = 680;
		static const int TILE_SIZE = 60;
		static const int CONF_VEL_PERSONAJE;
		static const int LONG_MARGEN_SCROLL = 30;
		static const string NOMBRE_ESCENARIO;
		static const string IMAGE_BASE_PATH;
		static const string AGE_OF_EMPIRES;
		static const string IMAGE_TILES_PATH;
		static const string IMAGE_PERSONAJES_PATH;
		static const int MAP_WIDTH = 15;							//esto vendría a ser el eje x
		static const int MAP_HEIGHT = 15 ;							//esto viene a ser el eje y
		static const int MEDIUM_SIZE = 3;
		static const int VELOCIDAD_SCROLL_UNO = 10;
		static const int VELOCIDAD_SCROLL_DOS = 30;
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
};


#endif /* SOURCE_MODELO_DEFAULTSETTINGS_H_ */
