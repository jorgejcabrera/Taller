/*
 * EntidadEstatica.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_ENTIDADESTATICA_H_
#define SOURCE_MODELO_ENTIDADESTATICA_H_

#include "EntidadPartida.h"

using namespace std;

class EntidadEstaticaVista: public EntidadPartida {
private:
	bool edificable;
	string tipo;

public:
	EntidadEstaticaVista();
	void destruir();
	EntidadEstaticaVista(int width,int length,string tipoEntidad, bool esEdificable, const string &sourceImage);
	EntidadEstaticaVista(int width,int length,string tipoEntidad, bool esEdificable);
	void drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos);
	virtual ~EntidadEstaticaVista();
};

#endif /* SOURCE_MODELO_ENTIDADESTATICA_H_ */
