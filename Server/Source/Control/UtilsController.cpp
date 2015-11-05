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


