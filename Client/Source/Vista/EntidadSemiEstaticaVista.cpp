/*
 * EntidadSemiEstaticaVista.cpp
 *
 *  Created on: 22 de set. de 2015
 *      Author: jorge
 */

#include "../../Headers/Vista/EntidadSemiEstaticaVista.h"

namespace std {

string getStringSize(EntidadPartidaVista* entidad){
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

EntidadSemiEstaticaVista::EntidadSemiEstaticaVista() {
	this->isCompleted = true;
}


EntidadSemiEstaticaVista::EntidadSemiEstaticaVista(int width, int length, float widthPixel, float lengthPixels,int fps) {
	//el ancho y el largo es siempre el del tamaño del tile
	this->width = width;
	this->length = length;
	this->widthPixel = widthPixel;
	this->lengthPixel = lengthPixels;
	this->framesPerSecond = fps;
	this->frame = 0;
	this->inDelayPeriod = false;
	this->sizeString = getStringSize(this);
	this->owner = "";
	this->isCompleted = true;
}

int EntidadSemiEstaticaVista::getFramesPerSecond(){
	return this->framesPerSecond;
}

void EntidadSemiEstaticaVista::setDelay(int delayFrames){
	this->delay = delayFrames;
}

int EntidadSemiEstaticaVista::getWidthPixel(){
	return this->widthPixel;
}

int EntidadSemiEstaticaVista::getLengthPixel(){
	return this->lengthPixel;
}

//seteo la cantidad de frames que tiene una linea del archivo para luego poder controlar el delay
void EntidadSemiEstaticaVista::setFramesInLineFile(int qty){
	this->framesInLineFile = qty;
}

int EntidadSemiEstaticaVista::getFramesInLineFile(){
	return this->framesInLineFile;
}

SDL_Rect EntidadSemiEstaticaVista::getPositionOfSprite(int ciclos){
		SDL_Rect srcrect = { this->frame * this->widthPixel, 0, this->widthPixel, this->lengthPixel };
		// solo de prueba los 50 fps del ciclo principal
		int ciclosPerFrame = 50 / framesPerSecond;

		if(this->inDelayPeriod){
			if((SDL_GetTicks()-this->delayIndex)>= (this->delay*1000)){
				this->inDelayPeriod = false;
			}
		}else{
			if( ciclos % ciclosPerFrame == 0){
				this->frame++;
				if( (this->frame % this->getFramesInLineFile()) == 0){
					this->frame = 0;
					if(this->delay>0){
						this->delayIndex = SDL_GetTicks();
						this->inDelayPeriod = true;
					}
				}
			}
		}

		return srcrect;
}

void EntidadSemiEstaticaVista::drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos){
	//primero tenemos que centrar la entidad semiestatica
	int widthScreen = this->widthPixel * this->width;
	int lengthScreen = this->lengthPixel*this->length;
	int posXScreen = (isometricPosition.first + offSetX) - this->widthPixel / 2 + DefaultSettings::getTileSize();
	int posYScreen = (isometricPosition.second + offSetY) - this->widthPixel / 2 - DefaultSettings::getTileSize() /2;
	PicassoHelper::GetInstance()->renderObject(this->getPathImage(),posXScreen,posYScreen,widthScreen,lengthScreen, this->getPositionOfSprite(ciclos));
}

EntidadSemiEstaticaVista::~EntidadSemiEstaticaVista() {
}

} /* namespace std */
