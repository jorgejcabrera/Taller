/*
 * Constantes.h
 *
 *  Created on: 2 de set. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_DEFAULTSETTINGS_H_
#define SOURCE_MODELO_DEFAULTSETTINGS_H_

#include <string>
#include <map>
using namespace std;

class DefaultSettings {
	private:
		static const int SCREEN_WIDTH = 1024;
		static const int SCREEN_HEIGHT = 860;
		static const int TILE_SIZE = 40;
		static const int CONF_VEL_PERSONAJE;
		static const int MARGEN_SCROLL = 30;
		static const string NOMBRE_ESCENARIO;
		static const int MAP_WIDTH = 15;		//esto vendría a ser el eje x
		static const int MAP_HEIGHT = 15 ;			//esto viene a ser el eje y

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
		static void trasladarse();
		static string imagePathByType(const string &object);
};


#endif /* SOURCE_MODELO_DEFAULTSETTINGS_H_ */