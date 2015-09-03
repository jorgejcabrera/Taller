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
#include <map>

using namespace std ;

class Juego {
private:
	defaultSettings_t defaultSettings;
	Mapa mapa;
	EntidadDinamica personajeSeleccionado;
	bool juegoFinalizado;
public:
	Juego();
	virtual ~Juego();

	//Intenta cargar la conf del yaml y setear los atributos al mapa, si por algún motivo no los encuentra setea los valores por default
	void comenzarPartida();

	void terminarJuego();

	bool getStatusPartida();
};

#endif /* SOURCE_MODELO_JUEGO_H_ */
