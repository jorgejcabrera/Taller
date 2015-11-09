/*
 * EntidadEstaticaVista.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "../../Headers/Vista/EntidadEstaticaVista.h"

using namespace std;

string getStringSize(EntidadPartidaVista* entidad){
	if(entidad->getWidth() == 3 && entidad->getLength() == 3){
		return "standarMediumSize";
	}else if(entidad->getWidth() == 4 && entidad->getLength() == 4){
		return "standardBigSize";
	}else if(entidad->getWidth() == 2 && entidad->getLength() == 2){
		return "standarSmallSize";
	}else if(entidad->getWidth() == 1 && entidad->getLength() == 1){
		return "standarMiniSize";
	}else if(entidad->getWidth() == 3 && entidad->getLength() == 4){
		return "mediumSize";
	}else{
		return "standarMediumSize";
	}
}

EntidadEstaticaVista::EntidadEstaticaVista(int width,int length){
	this->width = width;
	this->length = length;
	this->edificable = true;
	this->sizeString = getStringSize(this);
	this->owner = "";
}

void EntidadEstaticaVista::destruir(){
	this->~EntidadEstaticaVista();
}

void EntidadEstaticaVista::drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos){
	if(this->sizeString == "standarSmallSize"){
		PicassoHelper::GetInstance()->renderObject(this->getPathImage(), (isometricPosition.first+ offSetX) , (isometricPosition.second+ offSetY) ,this->getWidth() * 2 * DefaultSettings::getTileSize(), this->getLength() * DefaultSettings::getTileSize() * 2);
	}else if(this->sizeString =="standarMiniSize"){
		PicassoHelper::GetInstance()->renderObject(this->getPathImage(), (isometricPosition.first+ offSetX-10) , (isometricPosition.second+ offSetY-10) ,DefaultSettings::getTileSize(), DefaultSettings::getTileSize());
	}else{
		PicassoHelper::GetInstance()->renderObject(this->getPathImage(), (isometricPosition.first+ offSetX) , (isometricPosition.second+ offSetY) ,this->getWidth() * 2 * DefaultSettings::getTileSize(), (this->getLength()-1) * DefaultSettings::getTileSize() * 2);
	}
}

EntidadEstaticaVista::~EntidadEstaticaVista() {
}
