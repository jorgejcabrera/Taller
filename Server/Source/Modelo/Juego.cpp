/*
 * Juego.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/Juego.h"

using namespace std;

Juego::Juego() {
	gameSettings = GameSettings::GetInstance();
	this->mapa = new Mapa();
	this->resourseManager = new ResourceManager(this->mapa);
}

void Juego::createDinamicEntity(string owner){
	//TODO revisar que le ponemos en tipo
	pair<int,int> positionOfProtagonista = this->mapa->getAvailablePosition();
	EntidadDinamica* protagonista = new EntidadDinamica(gameSettings->getTipoProtagonista(),
														gameSettings->getVelocidadPersonaje(),
														positionOfProtagonista.first,
														positionOfProtagonista.second,
														gameSettings->getProtagonistaPixelDimension(),
														gameSettings->getProtagonistaPixelDimension());

	protagonista->setOwner(owner);
	protagonista->setScreenPosition(gameSettings->getPosXProtagonista(),gameSettings->getPosYProtagonista());
	protagonista->setVisibilityRange(gameSettings->getRangeVisibility());
	this->protagonistas.insert(make_pair(protagonista->getId(),protagonista));
	//defino una lista con los nuevos protagonistas para que se enteren los clientes anterores
	this->newProtagonistas.push_back(protagonista);
}

Mapa* Juego::getMap(){
	return this->mapa;
}

map<int,EntidadDinamica*> Juego::getProtagonistas(){
	return this->protagonistas;
}

list<EntidadDinamica*>* Juego::getNewProtagonistasToNotify(){
	return &this->newProtagonistas;
}

void Juego::cleanNewProtagonistas(){
	this->newProtagonistas.clear();
}

void Juego::setPlaceToGo(int idProtagonista, int x,int y){
	EntidadDinamica* protagonistaToUpdate = this->protagonistas.at(idProtagonista);
	PathFinder* pathF = new PathFinder(protagonistaToUpdate->getPosition()->first,
									  protagonistaToUpdate->getPosition()->second,
									  x,y,this->mapa,this->resourseManager);

	//calculo el camino minimo para llegar a destino
	list<pair<int,int> >* caminoMinimo = pathF->buscarCamino();
	delete pathF;
	protagonistaToUpdate->setPath(caminoMinimo);
	protagonistaToUpdate->setPathIsNew(true);
}

ResourceManager* Juego::getResourceManager(){
	return this->resourseManager;
}

Juego::~Juego() {
	for(map<int,EntidadDinamica*>::iterator it=this->protagonistas.begin(); it!=this->protagonistas.end(); ++it){
			delete(it->second);
	}
	delete(this->mapa);
	this->mapa = NULL;
	this->gameSettings=NULL;
}
