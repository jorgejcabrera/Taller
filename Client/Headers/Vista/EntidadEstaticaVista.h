/*
 * EntidadEstaticaVista.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_VISTA_ENTIDADESTATICAVISTA_H_
#define SOURCE_VISTA_ENTIDADESTATICAVISTA_H_

#include "../../Headers/Vista/EntidadPartidaVista.h"

using namespace std;

class EntidadEstaticaVista: public EntidadPartidaVista {
public:
	EntidadEstaticaVista();
	void destruir();
	EntidadEstaticaVista(int width,int length);
	void drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos);
	virtual ~EntidadEstaticaVista();

};

#endif /* SOURCE_VISTA_ENTIDADESTATICAVISTA_H_ */
