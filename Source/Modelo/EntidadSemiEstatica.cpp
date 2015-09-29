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


EntidadSemiEstatica::EntidadSemiEstatica(int width, int length, float widthPixel, float lengthPixels,int fps,const string &tipoEntidad,const string &pathImage) {
	//el ancho y el largo es siempre el del tamaño del tile
	this->width = width;
	this->length = length;
	this->widthPixel = widthPixel;
	this->lengthPixel = lengthPixels;
	this->framesPerSecond = fps;
	this->pathImage = pathImage;
	this->frame = 0;
	this->inDelayPeriod = false;
	this->delayIndex = 0;
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

pair<int,int>* EntidadSemiEstatica::getPosition(){
	return &this->position;
}

SDL_Rect EntidadSemiEstatica::getPositionOfSprite(int ciclos){
		SDL_Rect srcrect = { this->frame * this->widthPixel, 0, this->widthPixel, this->lengthPixel };
		// solo de prueba los 50 fps del ciclo principal
		int ciclosPerFrame = 50 / framesPerSecond;

		if(this->inDelayPeriod){
			//if(this->delayIndex <= (this->delay*this->framesPerSecond)){
			if(this->delayIndex <= this->delay){
				delayIndex++;
			}else{
				this->inDelayPeriod = false;
			}
		}else{
			if( ciclos % ciclosPerFrame == 0){
				this->frame++;
				if( (this->frame % this->getFramesInLineFile()) == 0){
					this->frame = 0;
					if(this->delay>0){
						this->delayIndex = 0;
						this->inDelayPeriod = true;
					}
				}
			}
		}

		return srcrect;
}

void EntidadSemiEstatica::drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos){
	//primero tenemos que centrar la entidad semiestatica
	int widthScreen = this->widthPixel * this->width;
	int lengthScreen = this->lengthPixel*this->length;
	int posXScreen = (isometricPosition.first + offSetX) - this->widthPixel / 2 + DefaultSettings::getTileSize();
	int posYScreen = (isometricPosition.second + offSetY) - this->widthPixel / 2 - DefaultSettings::getTileSize() /2;
	PicassoHelper::GetInstance()->renderObject(this->getPathImage(),posXScreen,posYScreen,widthScreen,lengthScreen, this->getPositionOfSprite(ciclos));
}

EntidadSemiEstatica::~EntidadSemiEstatica() {
}

} /* namespace std */
