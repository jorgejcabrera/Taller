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
	this->isCompleted = true;
	this->sizeString = getStringSize(this);
	this->owner = "";
	this->isCompleted = true;
}

bool EntidadEstaticaVista::isBuildingCompleted(){
	return this->isCompleted;
}

void EntidadEstaticaVista::setBuildingCompleted(bool completed){
	this->isCompleted = completed;
}

void EntidadEstaticaVista::destruir(){
	this->~EntidadEstaticaVista();
}

void EntidadEstaticaVista::drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos){
	int x;
	int y;
	int h;
	int w;
	if(this->sizeString == "standarSmallSize"){
		x = (isometricPosition.first+ offSetX);
		y= (isometricPosition.second+ offSetY);
		w = this->getWidth() * 2 * DefaultSettings::getTileSize();
		h= this->getLength() * DefaultSettings::getTileSize() * 2;
	}else if(this->sizeString =="standarMiniSize"){
		x = (isometricPosition.first+ offSetX-10);
		y = (isometricPosition.second+ offSetY-10);
		w = DefaultSettings::getTileSize();
		h = DefaultSettings::getTileSize();
	}else{
		x = (isometricPosition.first+ offSetX);
		y = (isometricPosition.second+ offSetY);
		w = this->getWidth() * 2 * DefaultSettings::getTileSize();
		h = (this->getLength()-1) * DefaultSettings::getTileSize() * 2;
	}


	if(this->isCompleted){
		PicassoHelper::GetInstance()->renderObject(this->getPathImage(), x, y, w, h);
	}else{
		PicassoHelper::GetInstance()->renderObjectGrey(this->getPathImage(), x, y, w, h);
	}
}

EntidadEstaticaVista::~EntidadEstaticaVista() {
}
