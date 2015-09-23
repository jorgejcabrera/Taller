/*
 * EntidadSemiEstatica.cpp
 *
 *  Created on: 22 de set. de 2015
 *      Author: jorge
 */

#include "EntidadSemiEstatica.h"

namespace std {

EntidadSemiEstatica::EntidadSemiEstatica() {
	// TODO Auto-generated constructor stub

}


EntidadSemiEstatica::EntidadSemiEstatica(int width, int length, float widthPixel, float lengthPixels,int fps,const string &tipoEntidad) {
	//el ancho y el largo es siempre el del tamaño del tile
	this->width = width;
	this->length = length;
	this->widthPixel = widthPixel;
	this->lengthPixel = lengthPixels;
	this->framesPerSecond = fps;
	this->pathImage = DefaultSettings::imagePathBuildingsByTypeAndAge(tipoEntidad, DefaultSettings::getAgeOfEmpires());

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

pair<int,int>* EntidadSemiEstatica::getPosition(){
	return &this->position;
}

SDL_Rect EntidadSemiEstatica::getPositionOfSprite(){
		SDL_Rect srcrect = { this->frame * this->widthPixel, 0, this->widthPixel, this->lengthPixel };
		if(this->inDelayPeriod){
			if(this->delayIndex <= (this->delay*this->framesPerSecond)){
				delayIndex++;
			}else{
				this->inDelayPeriod = false;
			}
		}else{
				this->frame++;
				if( (this->frame % this->getFramesInLineFile()) == 0){
					this->frame = 0;
					if(this->delay>0){
						this->delayIndex = 0;
						this->inDelayPeriod = true;
					}
				}
		}
		return srcrect;
}

void EntidadSemiEstatica::drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY){
	PicassoHelper::GetInstance()->renderObject(this->getPathImage(),(isometricPosition.first+ offSetX), (isometricPosition.second+ offSetY), this->widthPixel,this->lengthPixel, this->getPositionOfSprite());
}

EntidadSemiEstatica::~EntidadSemiEstatica() {
}

} /* namespace std */
