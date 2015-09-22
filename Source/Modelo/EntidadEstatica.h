/*
 * EntidadEstatica.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_ENTIDADESTATICA_H_
#define SOURCE_MODELO_ENTIDADESTATICA_H_

#include "EntidadPartida.h"
#include "DefaultSettings.h"
#include "PicassoHelper.h"

using namespace std;

class EntidadEstatica: public EntidadPartida {
private:
	bool edificable;
	string tipo;

public:
	EntidadEstatica();
	void destruir();
	EntidadEstatica(int width,int length,string tipoEntidad, bool esEdificable, const string &sourceImage);
	EntidadEstatica(int width,int length,string tipoEntidad, bool esEdificable);
	void drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY);
	virtual ~EntidadEstatica();
};

#endif /* SOURCE_MODELO_ENTIDADESTATICA_H_ */
