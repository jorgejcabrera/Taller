/*
 * EntidadEstatica.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "EntidadEstatica.h"

using namespace std;

EntidadEstatica::EntidadEstatica() {
}

EntidadEstatica::EntidadEstatica(string tipoEntidad, bool esEdificable, const string &sourceImage){
	edificable = esEdificable;
	tipo = tipoEntidad;
	pathImage = sourceImage;
}

EntidadEstatica::EntidadEstatica(string tipoEntidad, bool esEdificable){
	edificable = esEdificable;
	tipo = tipoEntidad;
	pathImage = DefaultSettings::imagePathByType(tipoEntidad);
}
string EntidadEstatica::getPathImage(){
	return pathImage;
}

EntidadEstatica::~EntidadEstatica() {
	// TODO Auto-generated destructor stub
}
