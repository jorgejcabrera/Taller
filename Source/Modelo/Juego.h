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
using namespace std ;

class Juego {
private:
	Mapa mapa;
	EntidadDinamica personajeSeleccionado;
	bool juegoFinalizado;
public:
	Juego();
	virtual ~Juego();
	void terminarJuego();
	bool getStatusPartida();
};

#endif /* SOURCE_MODELO_JUEGO_H_ */
