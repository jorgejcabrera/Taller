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
		x = (isometricPosition.first+ offSetX-5);
		y = (isometricPosition.second+ offSetY-10);
		w = DefaultSettings::getTileSize()*9/10;
		h = DefaultSettings::getTileSize()*9/10;
	}else{
		x = (isometricPosition.first+ offSetX);
		y = (isometricPosition.second+ offSetY);
		w = this->getWidth() * 2 * DefaultSettings::getTileSize();
		h = (this->getLength()-1) * DefaultSettings::getTileSize() * 2;
	}


	if(this->isCompleted){
		PicassoHelper::GetInstance()->renderObject(this->getPathImage(), x, y, w, h);
		if(this->isUnderAttack() && this->owner != "" && this->name!= "flag"){
			string pathFire = "../../Taller/Images/Personajes/fire.png";
			PicassoHelper::GetInstance()->renderObject(pathFire, x+(this->width*DefaultSettings::getTileSize())/2, y, DefaultSettings::getTileSize()*3, DefaultSettings::getTileSize()*3);
		}
	}else{
		PicassoHelper::GetInstance()->renderObjectGrey(this->getPathImage(), x, y, w, h);
	}
}

EntidadEstaticaVista::~EntidadEstaticaVista() {
}
