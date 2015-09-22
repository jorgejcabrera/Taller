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


EntidadSemiEstatica::EntidadSemiEstatica(string path,float x,float y, float widthPixel, float lengthPixels, int fps) {
		this->position.first = x;
		this->position.second = y;
		//el ancho y el largo es siempre el del tamaño del tile
		this->width = 3;
		this->length = 3;
		this->widthPixel = widthPixel;
		this->lengthPixel = lengthPixels;
		this->framesPerSecond = fps;
		this->pathImage=path;

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

void EntidadSemiEstatica::setInitialScreenPosition(float x,float y){
	// no borrar por favor
	this->screenPosition.first = x;
	this->screenPosition.second = y;
}

//seteo la cantidad de frames que tiene una linea del archivo para luego poder controlar el delay
void EntidadSemiEstatica::setFramesInLineFile(int qty){
	this->framesInLineFile = qty;
}

int EntidadSemiEstatica::getFramesInLineFile(){
	return this->framesInLineFile;
}

pair<float,float>* EntidadSemiEstatica::getScreenPosition(){
	return &this->screenPosition;
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
					cout << "ENTRE EN IF" <<endl;
					this->frame = 0;
					if(this->delay>0){
						this->delayIndex = 0;
						this->inDelayPeriod = true;
					}
				}
		}
		return srcrect;
}

void EntidadSemiEstatica::dibujate(pair<int,int> isometricPosition, int offSetX, int offSetY){
	//cout << "image " << this->getPathImage() <<" FIRST " << screenPosition.first << " OFSETX " << offSetX << " SECOND " << screenPosition.second  << "LENGTH PIXEL: " << this->getLengthPixel() << " TILE " << DefaultSettings::getTileSize() <<endl;
	PicassoHelper::GetInstance()->renderObject(this->getPathImage(), screenPosition.first - DefaultSettings::getTileSize()/2 + offSetX, screenPosition.second - this->getLengthPixel() / 2 + offSetY, DefaultSettings::getTileSize(), DefaultSettings::getTileSize(), this->getPositionOfSprite());
	cout << "PASEEEE" << endl;

}




EntidadSemiEstatica::~EntidadSemiEstatica() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
