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

using namespace std;

class EntidadEstatica: public EntidadPartida {
private:
	bool edificable;
	string tipo;
	string pathImage;

public:
	EntidadEstatica();
	EntidadEstatica(string tipoEntidad, bool esEdificable, const string &sourceImage);
	EntidadEstatica(string tipoEntidad, bool esEdificable);

	string getPathImage();
	virtual ~EntidadEstatica();
};

#endif /* SOURCE_MODELO_ENTIDADESTATICA_H_ */
