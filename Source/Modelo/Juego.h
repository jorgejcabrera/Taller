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
namespace std {

class Juego {
private:
	Mapa mapa;
	EntidadDinamica personajeSeleccionado;
public:
	Juego();
	virtual ~Juego();
};

} /* namespace std */

#endif /* SOURCE_MODELO_JUEGO_H_ */
