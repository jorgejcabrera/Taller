/*
 * EntidadEstaticaVista.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_VISTA_ENTIDADESTATICAVISTA_H_
#define SOURCE_VISTA_ENTIDADESTATICAVISTA_H_

#include "EntidadPartidaVista.h"

using namespace std;

class EntidadEstaticaVista: public EntidadPartidaVista {
public:
	EntidadEstaticaVista();
	void destruir();
	EntidadEstaticaVista(int width,int length);
	void drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos);
	bool isBuildingCompleted();
	void setBuildingCompleted(bool completed);
	virtual ~EntidadEstaticaVista();

};

#endif /* SOURCE_VISTA_ENTIDADESTATICAVISTA_H_ */
