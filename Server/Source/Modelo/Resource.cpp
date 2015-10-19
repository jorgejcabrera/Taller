/*
 * Resource.cpp
 *
 *  Created on: Oct 17, 2015
 *      Author: juan
 */

#include "../../Headers/Modelo/Resource.h"

using namespace std;

Resource::Resource(string tipo,int x,int y) {
	this->position.first = x;
	this->position.second = y;
	this->width = 1;
	this->length = 1;
	this->tipo = tipo;
	if(tipo == "chori")
		this->pathImage = "../../Taller/Images/Resources/chori.png";
	if(tipo == "wood")
		this->pathImage = "../../Taller/Images/Resources/Wood.png";
	if(tipo == "gold")
		this->pathImage = "../../Taller/Images/Resources/gold.png";
	this->sizeString = "standarSmallSize";

}

void Resource::drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos){

	PicassoHelper::GetInstance()->renderObject(this->getPathImage(), (isometricPosition.first+ offSetX + 30) , (isometricPosition.second+ offSetY + 65) ,this->getWidth() * DefaultSettings::getTileSize() / 2, this->getLength() * DefaultSettings::getTileSize() / 2);
}

string Resource::getTipo(){
	return this->tipo;
}

Resource::~Resource() {
	// TODO Auto-generated destructor stub
}

