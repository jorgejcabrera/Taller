/*
 * Mapa.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_MAPA_H_
#define SOURCE_MODELO_MAPA_H_

#include "EntidadPartida.h"
#include "Tile.h"
#include "DefaultSettings.h"
#include <list>

using namespace std;

class Mapa {
private:
	DefaultSettings* defaultSettings = new DefaultSettings();
	list<EntidadPartida> entidades;
	list<Tile> tiles;
public:
	Mapa();
	virtual ~Mapa();
};


#endif /* SOURCE_MODELO_MAPA_H_ */
