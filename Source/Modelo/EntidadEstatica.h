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
	int width;
	int length;
	bool edificable;
	string tipo;
	string pathImage;

public:
	EntidadEstatica();
	EntidadEstatica(int width,int length,string tipoEntidad, bool esEdificable, const string &sourceImage);
	EntidadEstatica(int width,int length,string tipoEntidad, bool esEdificable);
	int getWidth();
	int getLength();
	string getPathImage();
	virtual ~EntidadEstatica();
};

#endif /* SOURCE_MODELO_ENTIDADESTATICA_H_ */
