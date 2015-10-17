/*
 * EntidadConfig.cpp
 *
 *  Created on: 17 de oct. de 2015
 *      Author: jorlando
 */
#include "../../Headers/Modelo/EntidadConfig.h"


EntidadConfig::EntidadConfig() {
}

EntidadConfig::~EntidadConfig() {
}

EntidadConfig::EntidadConfig(string nameNew, string pathNew, int anchoNew, int altoNew, int fpsNew, int delayNew, int totalFramesLineNew, int pixelsDimensionNew){
	this->name = nameNew;
	this->path = pathNew;
	this->ancho = anchoNew;
	this->alto = altoNew;
	this->fps = fpsNew;
	this->delay = delayNew;
	this->totalFramesLine = totalFramesLineNew;
	this->pixelsDimension = pixelsDimensionNew;
}

string EntidadConfig::getName(){
	return this->name;
}

string EntidadConfig::getPath(){
	return this->path;
}

int EntidadConfig::getAncho(){
	return this->ancho;
}

int EntidadConfig::getAlto(){
	return this->alto;
}

int EntidadConfig::getFps(){
	return this->fps;
}

int EntidadConfig::getDelay(){
	return this->delay;
}

int EntidadConfig::getTotalFramesLine(){
	return this->totalFramesLine;
}

int EntidadConfig::getPixelsDimension(){
	return this->pixelsDimension;
}
