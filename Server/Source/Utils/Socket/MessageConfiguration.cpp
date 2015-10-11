/*
 * MessageConfiguration.cpp
 *
 *  Created on: 10 de oct. de 2015
 *      Author: jorlando
 */

#include "../../../Headers/Utils/Socket/MessageConfiguration.h"


MessageConfiguration::MessageConfiguration() {
}

MessageConfiguration::MessageConfiguration(string name, string path, int width, int heigth){
	this->msg.nombre = name;
	this->msg.imagen = path;
	this->msg.ancho_base = width;
	this->msg.alto_base = heigth;
	this->msg.fps = 0;
	this->msg.delay = 0;
	this->msg.total_frames_line = 0;
	this->msg.pixels_dimension = 0;
}

MessageConfiguration::MessageConfiguration(string name, string path, int width, int heigth, int fpsParam, int delayParam, int totalFramesLine, int pixelConfig){
	this->msg.nombre = name;
	this->msg.imagen = path;
	this->msg.ancho_base = width;
	this->msg.alto_base = heigth;
	this->msg.fps = fpsParam;
	this->msg.delay = delayParam;
	this->msg.total_frames_line = totalFramesLine;
	this->msg.pixels_dimension = pixelConfig;
}

void MessageConfiguration::setFPS(int fpsToSet){
	this->msg.fps = fpsToSet;
}

void MessageConfiguration::setDelay(int delayToSet){
	this->msg.delay = delayToSet;
}

void MessageConfiguration::setTotalFramesLine(int totalFramesInLine){
	this->msg.total_frames_line = totalFramesInLine;
}

void MessageConfiguration::setPixel(int pixelToSet){
	this->msg.pixels_dimension = pixelToSet;
}

MessageConfiguration::~MessageConfiguration(){
}

string MessageConfiguration::toString(){
	stringstream ss;
	ss << "nombre:" << this->msg.nombre;
	ss <<";imagen:"<< this->msg.imagen;
	ss <<";ancho_base:" << this->msg.ancho_base;
	ss <<";alto_base:"<<this->msg.alto_base;
	ss <<";fps:"<<this->msg.fps;
	ss <<";delay:"<<this->msg.delay;
	ss <<";total_frames_line:"<<this->msg.total_frames_line;
	ss <<";pixels_dimension:"<<this->msg.pixels_dimension;
	ss <<";";
	return ss.str();
}
