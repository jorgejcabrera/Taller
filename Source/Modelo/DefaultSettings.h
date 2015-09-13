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
		static const int SCREEN_HEIGHT = 860;
		static const int TILE_SIZE = 40;
		static const int CONF_VEL_PERSONAJE;
		static const int MARGEN_SCROLL = 30;
		static const string NOMBRE_ESCENARIO;
		static const string IMAGE_BASE_PATH;
		static const string AGE_OF_EMPIRES;
		static const int MAP_WIDTH = 14;							//esto vendría a ser el eje x
		static const int MAP_HEIGHT = 14 ;							//esto viene a ser el eje y
		static const int MEDIUM_SIZE = 3;
	public:
		DefaultSettings();
		virtual ~DefaultSettings();
		static int getScreenWidth();
		static int getScreenHeight();
		static int getTileSize();
		static int getMargenScroll();
		static string getNombreEscenario();
		static int getMapWidth();
		static int getMapHeight();
		static int getMediumSize();
		static string getAgeOfEmpires();
		static string imagePathByTypeAndAge(const string &object,const string &age);
		static string defaultImage();
		static bool isEntityTypeValid(const string &type);
};


#endif /* SOURCE_MODELO_DEFAULTSETTINGS_H_ */
