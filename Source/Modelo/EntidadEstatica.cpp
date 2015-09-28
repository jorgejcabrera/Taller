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

EntidadEstatica::EntidadEstatica(int width,int length,string tipoEntidad, bool esEdificable, const string &sourceImage){
	this->width = width;
	this->length = length;
	this->edificable = esEdificable;
	this->tipo = tipoEntidad;
	this->pathImage = sourceImage;
	this->sizeString = getStringSize(this);
}

EntidadEstatica::EntidadEstatica(int width,int length,string tipoEntidad, bool esEdificable){
	this->width = width;
	this->length = length;
	this->edificable = esEdificable;
	this->tipo = tipoEntidad;
	this->sizeString = getStringSize(this);
}

void EntidadEstatica::destruir(){
	this->~EntidadEstatica();
}

void EntidadEstatica::drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos){
	if( this->sizeString == "standarSmallSize"){
		PicassoHelper::GetInstance()->renderObject(this->getPathImage(), (isometricPosition.first+ offSetX) , (isometricPosition.second+ offSetY) ,this->getWidth() * 2 * DefaultSettings::getTileSize(), this->getLength() * DefaultSettings::getTileSize() * 2);
	}else{
		PicassoHelper::GetInstance()->renderObject(this->getPathImage(), (isometricPosition.first+ offSetX) , (isometricPosition.second+ offSetY) ,this->getWidth() * 2 * DefaultSettings::getTileSize(), (this->getLength()-1) * DefaultSettings::getTileSize() * 2);
	}
}

EntidadEstatica::~EntidadEstatica() {
}
