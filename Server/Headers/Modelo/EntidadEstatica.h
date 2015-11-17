/*
 * EntidadEstatica.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_ENTIDADESTATICA_H_
#define SOURCE_MODELO_ENTIDADESTATICA_H_

#include "GameSettings.h"
#include "EntidadPartida.h"

using namespace std;

class EntidadEstatica: public EntidadPartida {
public:
	EntidadEstatica();
	EntidadEstatica(string nameEntity, int width,int length, bool isCompletedConstruction);
	virtual ~EntidadEstatica();
};

#endif /* SOURCE_MODELO_ENTIDADESTATICA_H_ */
