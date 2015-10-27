/*
 * EntidadDinamicaVista.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "../../Headers/Vista/EntidadDinamicaVista.h"

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
	this->velocidad = 10;
	this->camino = new list<pair<int,int> >();
}

string EntidadDinamicaVista::getName(){
	return this->name;
}

void EntidadDinamicaVista::setInitialScreenPosition(float x,float y){
	this->screenPosition.first = x;
	this->screenPosition.second = y;
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

void EntidadDinamicaVista::setFramesInLineFile(int qty){
	this->framesInLineFile = qty;
}

int EntidadDinamicaVista::getFramesInLineFile(){
	return this->framesInLineFile;
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

pair<float,float> EntidadDinamicaVista::getScreenPosition(){
	return this->screenPosition;
}
void EntidadDinamicaVista::setScreenPosition(float x,float y){
	this->destinoX = x;
	this->destinoY = y;

	//calcula la velocidad en cada eje para ir al destino
	float distanciaDest = distanciaA(x,y);
	if(distanciaDest > 0) this->caminando = true;
	else this->caminando = false;

	float seno = distanciaEnY(y) / distanciaDest;
	float coseno = distanciaEnX(x) / distanciaDest;

	this->vecVelocity.first = velocidad * coseno;
	this->vecVelocity.second = velocidad * seno;
}

float EntidadDinamicaVista::distanciaA(float x, float y){
	float distY = (screenPosition.second - y);
	float distX = (screenPosition.first - x);
	return sqrt((distX * distX) +  (distY * distY));
}

float EntidadDinamicaVista::distanciaEnY(float y){
	float res;
	if(screenPosition.second > y) res = screenPosition.second - y;
	else res = y - screenPosition.second;
	return res;
}

float EntidadDinamicaVista::distanciaEnX(float x){
	float res;
	if(screenPosition.first > x) res = screenPosition.first - x;
	else res = x - screenPosition.first;
	return res;
}

Direccion EntidadDinamicaVista::getDireccionHorizontal(){
	Direccion dHorizontal = Sindireccion;
	if(caminando && (vecVelocity.first / this->velocidad > 0.38)){
		if(screenPosition.first > destinoX) dHorizontal = Oeste;
		else dHorizontal = Este;
	}
	return dHorizontal;
}
Direccion EntidadDinamicaVista::getDireccionVertical(){
	//para que la direccion sea norte/sur el seno del angulo tiene que ser mayor a 0.38
	// equivale a un angulo de 22,5 grados o mas

	Direccion dVertical = Sindireccion;
	if(caminando && (vecVelocity.second / velocidad > 0.38 )){
		if(screenPosition.second > destinoY) dVertical = Norte;
		else dVertical = Sur;
	}
	return dVertical;
}

Direccion EntidadDinamicaVista::getDireccion(){
	Direccion dir = Sindireccion;
	Direccion dVertical = getDireccionVertical();
	Direccion dHorizontal = getDireccionHorizontal();

	switch(dVertical){
	case Sindireccion: dir = dHorizontal; break;
	case Norte: switch(dHorizontal){
				case Sindireccion: dir = Norte;break;
				case Este: dir = Noreste;break;
				case Oeste: dir = Noroeste;
				} break;
	case Sur: switch(dHorizontal){
			  case Sindireccion: dir = Sur;break;
			  case Este: dir = Sureste;break;
			  case Oeste: dir = Suroeste;break;
			  }
	}
	return dir;
}

void EntidadDinamicaVista::walk(){
	this->caminando = true;
}

void EntidadDinamicaVista::stopWalk(){
	this->caminando = false;
}

bool EntidadDinamicaVista::isWalking(){
	return caminando;
}

void EntidadDinamicaVista::setPosition(int x,int y){
	this->position.first= x;
	this->position.second = y;
}

void EntidadDinamicaVista::trasladarse(){

	if(distanciaEnX(destinoX) <= vecVelocity.first)
			screenPosition.first = destinoX;

	if(distanciaEnY(destinoY) <= vecVelocity.second)
			screenPosition.second = destinoY;

	if(distanciaEnX(destinoX) <= vecVelocity.first && distanciaEnY(destinoY) <= vecVelocity.first)
		caminando = false;

	if(caminando){
		if(screenPosition.first > destinoX)
			screenPosition.first -= vecVelocity.first;
		if(screenPosition.first < destinoX)
			screenPosition.first += vecVelocity.first;
		if(screenPosition.second > destinoY)
			screenPosition.second -= vecVelocity.second;
		if(screenPosition.second < destinoY)
			screenPosition.second += vecVelocity.second;
	}
}



int EntidadDinamicaVista::getFramesPerSecond(){
	return this->framesPerSecond;
}

void EntidadDinamicaVista::addTileToPath(int x,int y){
	pair<int,int> newTile;
	newTile.first = x;
	newTile.second = y;

	this->camino->push_back(newTile);
}

list<pair<int,int> >* EntidadDinamicaVista::getCamino(){
	return this->camino;
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
	ss << "name: "<< this->name <<"; position:["<< this->position.first<<";"<<this->position.second<<"]"<<"; destino: ["<<this->destinoX<<";"<<this->destinoY<<"];";
	return ss.str();
}

int EntidadDinamicaVista::getRangeVisibility() {
	return this->rangeVisibility;
}

EntidadDinamicaVista::~EntidadDinamicaVista() {
	delete this->camino;
}
