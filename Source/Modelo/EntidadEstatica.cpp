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

EntidadEstatica::EntidadEstatica(int width,int length,string tipoEntidad, bool esEdificable, const string &sourceImage){
	this->width = width;
	this->length = length;
	edificable = esEdificable;
	tipo = tipoEntidad;
	pathImage = sourceImage;
}

EntidadEstatica::EntidadEstatica(int width,int length,string tipoEntidad, bool esEdificable){
		this->width = width;
		this->length = length;
		edificable = esEdificable;
		tipo = tipoEntidad;
		pathImage = DefaultSettings::imagePathByType(tipoEntidad);
}
string EntidadEstatica::getPathImage(){
	return pathImage;
}

/*int EntidadEstatica::getWidth(){
	return this->width;
}

int EntidadEstatica::getLength(){
	return this->length;
}*/

EntidadEstatica::~EntidadEstatica() {
	// TODO Auto-generated destructor stub
}
