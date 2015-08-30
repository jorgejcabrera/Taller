/*
 * Mapa.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_MAPA_H_
#define SOURCE_MODELO_MAPA_H_

#include "EntidadPartida.h"
#include <list>

namespace std {

class Mapa {
private:
	std::list<EntidadPartida> entidades;
public:
	Mapa();
	virtual ~Mapa();
};

} /* namespace std */

#endif /* SOURCE_MODELO_MAPA_H_ */
