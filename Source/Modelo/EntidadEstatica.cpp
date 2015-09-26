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
}

void EntidadEstatica::destruir(){
	this->~EntidadEstatica();
}

void EntidadEstatica::drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos){
	PicassoHelper::GetInstance()->renderObject(this->getPathImage(), (isometricPosition.first+ offSetX) , (isometricPosition.second+ offSetY) ,this->getWidth() * 2 * DefaultSettings::getTileSize(), (this->getLength()-1) * DefaultSettings::getTileSize() * 2);
}

EntidadEstatica::~EntidadEstatica() {
}
