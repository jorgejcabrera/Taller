/*
 * UtilsController.cpp
 *
 *  Created on: 17 de set. de 2015
 *      Author: jorge
 */

#include "../../Headers/Control/UtilsController.h"
UtilsController* UtilsController::instance = NULL;


UtilsController::UtilsController() {
	gameSettings = GameSettings::GetInstance();
}

UtilsController* UtilsController::GetInstance(){
	if(!instance)
		instance = new UtilsController();
	return instance;
}

pair<int,int> UtilsController::convertToCartesian(int xScreen,int yScreen){
	int startMapX = gameSettings->getScreenWidth() / 2 + gameSettings->getTileSize();
	int x = ( yScreen * 2 + xScreen - startMapX) / (gameSettings->getTileSize() * 2);
	int y = yScreen / (gameSettings->getTileSize() / 2) - x;
	pair<int,int> cartesianPosition;
	cartesianPosition.first = x;
	cartesianPosition.second = y;
	return cartesianPosition;
}

pair<int,int> UtilsController::getIsometricPosition(EntidadPartida* entidad){
	pair<int,int> isometricPosition;
	//hacemos coincidir el vertice superior izquierdo de la entidad con el tile
	isometricPosition.first = (entidad->getPosition()->first - entidad->getPosition()->second) * gameSettings->getTileSize() + gameSettings->getScreenWidth() / 2;
	isometricPosition.second = (entidad->getPosition()->first + entidad->getPosition()->second) * gameSettings->getTileSize() / 2  ;

	//ahora hay que centrar la entidad segun su tamaño
	stringSize stringSize = this->getStringSize(entidad);
	if ( stringSize == standarMediumSize){
		isometricPosition.first = isometricPosition.first - (entidad->getWidth()-1)  *  gameSettings->getTileSize();
		isometricPosition.second =isometricPosition.second - (entidad->getLength()-1) *  gameSettings->getTileSize()/2;
	}else if( stringSize == standardBigSize){
		isometricPosition.first = isometricPosition.first - (entidad->getWidth()-1)  *  gameSettings->getTileSize();
		isometricPosition.second =isometricPosition.second - (entidad->getLength()-1) *  gameSettings->getTileSize()/2 - DefaultSettings::getTileSize()/2;	//TODO de donde se esta sacando el valor del tile???!
	}
	return isometricPosition;
}

stringSize UtilsController::getStringSize(EntidadPartida* entidad){
	if(entidad->getWidth() == 3 && entidad->getLength() == 3){
		return standarMediumSize;
	}else if(entidad->getWidth() == 4 && entidad->getLength() == 4){
		return standardBigSize;
	}else if(entidad->getWidth() == 2 && entidad->getLength() == 2){
		return standarSmallSize;
	}else{
		return standarMediumSize;
	}
}


pair<int,int> UtilsController::getIsometricPosition(int x,int y){
	pair<int,int> isometricPosition;
	//hacemos coincidir el vertice superior izquierdo de la entidad con el tile
	isometricPosition.first = ( x - y) * gameSettings->getTileSize() + gameSettings->getScreenWidth() / 2;
	isometricPosition.second = ( x + y) * gameSettings->getTileSize() / 2  ;

	//TODO revisar si las entidades tienen que tener siempre ancho y tamaño 1
	//ahora hay que centrar la entidad con el tile. Por default las entidades tienen ancho y largo 1
	isometricPosition.first = isometricPosition.first + gameSettings->getTileSize();
	isometricPosition.second = isometricPosition.second + gameSettings->getTileSize()/2;
	return isometricPosition;
}

UtilsController::~UtilsController() {
	this->instance = NULL;
}


