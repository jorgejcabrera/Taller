/*
 * EntidadEstatica.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_ENTIDADESTATICA_H_
#define SOURCE_MODELO_ENTIDADESTATICA_H_

#include "EntidadPartida.h"

namespace std {

class EntidadEstatica: public EntidadPartida {
public:
	EntidadEstatica();
	virtual ~EntidadEstatica();
};

} /* namespace std */

#endif /* SOURCE_MODELO_ENTIDADESTATICA_H_ */
