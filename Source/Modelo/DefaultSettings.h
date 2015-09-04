/*
 * Constantes.h
 *
 *  Created on: 2 de set. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_DEFAULTSETTINGS_H_
#define SOURCE_MODELO_DEFAULTSETTINGS_H_

#include <string>
using namespace std;

class DefaultSettings {
	private:
		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
		int TILE_SIZE;
		int CONF_VEL_PERSONAJE;
		int MARGEN_SCROLL;
		string NOMBRE_ESCENARIO;
		int ESCENARIO_ANCHO;
		int ESCENARIO_ALTO;
	public:
		DefaultSettings();
		virtual ~DefaultSettings();
		int getScreenWidth();
		int getScreenHeight();
		int getTileSize();
		int getMargenScroll();
		string getNombreEscenario();
		int getEscenarioAncho();
		int getEscenarioAlto();
		void setTileSize(int value);
		void trasladarse();
};


#endif /* SOURCE_MODELO_DEFAULTSETTINGS_H_ */
