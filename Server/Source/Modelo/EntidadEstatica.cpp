/*
 * EntidadEstatica.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/EntidadEstatica.h"

using namespace std;

string getStringSize(EntidadPartida* entidad){
	if(entidad->getWidth() == 3 && entidad->getLength() == 3){
		return "standarMediumSize";
	}else if(entidad->getWidth() == 4 && entidad->getLength() == 4){
		return "standardBigSize";
	}else if(entidad->getWidth() == 2 && entidad->getLength() == 2){
		return "standarSmallSize";
	}else if(entidad->getWidth() == 3 && entidad->getLength() == 4){
		return "mediumSize";
	}else{
		return "standarMediumSize";
	}
}

EntidadEstatica::EntidadEstatica() {
}

EntidadEstatica::EntidadEstatica(string nameEntity, int width,int length, bool esEdificable){
	this->width = width;
	this->length = length;
	this->edificable = esEdificable;
	this->name = nameEntity;
	this->sizeString = getStringSize(this);
}

void EntidadEstatica::destruir(){
	this->~EntidadEstatica();
}

EntidadEstatica::~EntidadEstatica() {
}
