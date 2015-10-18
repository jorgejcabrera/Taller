/*
 * Resource.cpp
 *
 *  Created on: Oct 17, 2015
 *      Author: juan
 */

#include "../../Headers/Modelo/Resource.h"

using namespace std;

Resource::Resource(int x,int y) {
	this->position.first = x;
	this->position.second = y;
	this->width = 1;
	this->length = 1;
	this->pathImage = "../../Taller/Images/Resources/Wood.png";
	this->sizeString = "standarSmallSize";

}

void Resource::drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos){

	PicassoHelper::GetInstance()->renderObject(this->getPathImage(), (isometricPosition.first+ offSetX + 15) , (isometricPosition.second+ offSetY + 55) ,this->getWidth() * DefaultSettings::getTileSize(), this->getLength() * DefaultSettings::getTileSize());
}

Resource::~Resource() {
	// TODO Auto-generated destructor stub
}

