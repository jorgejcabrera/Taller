/*
 * EntidadDinamicaVista.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "../../Headers/Vista/EntidadDinamicaVista.h"

/*EntidadDinamicaVista::EntidadDinamicaVista(){
}*/

EntidadDinamicaVista::EntidadDinamicaVista() {
	this->caminando = false;
	this->width = 50;
	this->length = 50;
}

EntidadDinamicaVista::EntidadDinamicaVista(string myName, float widthPixel, float lengthPixels, int fps){
	this->name = myName;
	this->caminando = false;
	this->width = 1;
	this->length = 1;
	this->widthPixel = widthPixel;
	this->lengthPixel = lengthPixels;
	if(fps > 50) fps = 50;
	this->framesPerSecond = fps;
	this->inDelayPeriod = false;
}

SDL_Rect EntidadDinamicaVista::getPositionOfSprite(int ciclos){
	int ciclesPerFrame = 50 / this->framesPerSecond;

	int lineaSprite = this->getLineSprite(this->getDireccion());
	SDL_Rect srcrect = { this->frame * this->widthPixel, this->lengthPixel*lineaSprite, this->widthPixel, this->lengthPixel };
	if(this->inDelayPeriod){
		if((SDL_GetTicks()-this->delayIndex)>= (this->delay*1000)){
			this->inDelayPeriod = false;
		}
	}else{
			if(!this->caminando){
				this->frame = 0;
			}else{
				if(ciclos % ciclesPerFrame == 0){
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
	}

	return srcrect;
}

void EntidadDinamicaVista::setInitialScreenPosition(float x,float y){
	this->screenPosition.first = x;
	this->screenPosition.second = y;
}

//seteo la cantidad de frames que tiene una linea del archivo para luego poder controlar el delay
void EntidadDinamicaVista::setFramesInLineFile(int qty){
	this->framesInLineFile = qty;
}

int EntidadDinamicaVista::getFramesInLineFile(){
	return this->framesInLineFile;
}

pair<float,float>* EntidadDinamicaVista::getScreenPosition(){
	return &this->screenPosition;
}

pair<int,int>* EntidadDinamicaVista::getPosition(){
	return &this->position;
}

int EntidadDinamicaVista::getWidthPixel(){
	return this->widthPixel;
}

int EntidadDinamicaVista::getLengthPixel(){
	return this->lengthPixel;
}

Direccion EntidadDinamicaVista::getDireccion(){
	//TODO: decidir la direccion en base a lo que dice el mensaje
	Direccion dir = Sindireccion;
	return dir;
}

int EntidadDinamicaVista::getLineSprite(Direccion dir){
	switch(dir){
	case Norte: return 1; break;
	case Noreste: return 2; break;
	case Este: return 0; break;
	case Sureste: return 5; break;
	case Sur: return 4; break;
	case Suroeste: return 6; break;
	case Oeste: return 7; break;
	case Noroeste: return 3; break;
	case Sindireccion: return 0; break;
	}
}

void EntidadDinamicaVista::setScreenPosition(float x,float y){
	this->destinoX = x;
	this->destinoY = y;
}


int EntidadDinamicaVista::getFramesPerSecond(){
	return this->framesPerSecond;
}

void EntidadDinamicaVista::setDelay(int delayFrames){
	this->delay = delayFrames;
}

void EntidadDinamicaVista::destruir(){
	this->~EntidadDinamicaVista();
}

void EntidadDinamicaVista::drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY){
}

string EntidadDinamicaVista::toString(){
	stringstream ss;
	ss << "name: "<<this->name <<"; screenPosition: ["<<screenPosition.first
	<<";"<<screenPosition.second<<"]"<<"; destino: ["<<this->destinoX<<";"<<this->destinoY<<"];";
	return ss.str();
}

EntidadDinamicaVista::~EntidadDinamicaVista() {
}
