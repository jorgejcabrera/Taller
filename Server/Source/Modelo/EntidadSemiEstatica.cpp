/*
 * EntidadSemiEstatica.cpp
 *
 *  Created on: 22 de set. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/EntidadSemiEstatica.h"

namespace std {

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

EntidadSemiEstatica::EntidadSemiEstatica() {
}


EntidadSemiEstatica::EntidadSemiEstatica(string nameEntity, int width, int length, float widthPixel, float lengthPixels,int fps) {
	//el ancho y el largo es siempre el del tamaño del tile
	this->width = width;
	this->length = length;
	this->widthPixel = widthPixel;
	this->lengthPixel = lengthPixels;
	this->framesPerSecond = fps;
	this->name = nameEntity;
	this->frame = 0;
	this->sizeString = getStringSize(this);
}

int EntidadSemiEstatica::getFramesPerSecond(){
	return this->framesPerSecond;
}

void EntidadSemiEstatica::setDelay(int delayFrames){
	this->delay = delayFrames;
}

int EntidadSemiEstatica::getWidthPixel(){
	return this->widthPixel;
}

int EntidadSemiEstatica::getLengthPixel(){
	return this->lengthPixel;
}

//seteo la cantidad de frames que tiene una linea del archivo para luego poder controlar el delay
void EntidadSemiEstatica::setFramesInLineFile(int qty){
	this->framesInLineFile = qty;
}

int EntidadSemiEstatica::getFramesInLineFile(){
	return this->framesInLineFile;
}

EntidadSemiEstatica::~EntidadSemiEstatica() {
}

} /* namespace std */
