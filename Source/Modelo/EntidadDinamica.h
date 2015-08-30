/*
 * EntidadDinamica.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_ENTIDADDINAMICA_H_
#define SOURCE_MODELO_ENTIDADDINAMICA_H_

#include "EntidadPartida.h"

namespace std {

class EntidadDinamica: public EntidadPartida {
private:
	int velocidad;
public:
	EntidadDinamica();
	virtual ~EntidadDinamica();
	void trasladarse();
};

} /* namespace std */

#endif /* SOURCE_MODELO_ENTIDADDINAMICA_H_ */
