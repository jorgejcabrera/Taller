/*
 * Juego.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_JUEGO_H_
#define SOURCE_MODELO_JUEGO_H_

#include "Mapa.h"
#include "EntidadDinamica.h"
#include "DefaultSettings.h"
#include <map>

using namespace std ;

class Juego {
private:
	Mapa mapa;
	EntidadDinamica personajeSeleccionado;
	DefaultSettings* defaultSettings = new DefaultSettings();
	bool juegoFinalizado;
	void setTilesPosition();
	void setTilesLowerPosition(int cant);
	void setTilesTopPosition(int cant);
public:
	Juego();
	virtual ~Juego();

	//Intenta cargar la conf del yaml y setear los atributos al mapa, si por algún motivo no los encuentra setea los valores por default
	void comenzarPartida();

	void terminarJuego();

	bool getStatusPartida();
};

#endif /* SOURCE_MODELO_JUEGO_H_ */
