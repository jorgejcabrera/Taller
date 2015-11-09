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

pair<int,int> Juego::createEntitiesForClient(string owner, int clientIndex){

	int width = this->gameSettings->getMapWidth();
	int height = this->gameSettings->getMapHeight();
	int xOriginClientSection;
	int yOriginClientSection;
	switch(clientIndex){
		case 0:
			xOriginClientSection = 0;
			yOriginClientSection = 0;
			break;
		case 1:
			xOriginClientSection = (width/2);
			yOriginClientSection = 0;
			break;
		case 2:
			xOriginClientSection = (width/2);
			yOriginClientSection = (height/2);
			break;
		case 3:
			xOriginClientSection = 0;
			yOriginClientSection = (height/2);
			break;
	}

	//Creo el centro civico del jugador
	string nombre = "Barracks";
	pair<int,int> dimension = this->gameSettings->getConfigDimensionOfEntity(nombre);
	int xOrigin =  xOriginClientSection+width/4;
	int yOrigin =  yOriginClientSection+height/4;

	EntidadPartida* edificioCreado = new EntidadEstatica(nombre,dimension.first,dimension.second,true);
	edificioCreado->setPosition(xOrigin,yOrigin);
	edificioCreado->setOwner(owner);
	this->mapa->pushEntity(edificioCreado);

	//Caclulo el offset inicial
	int xOffset = ((xOrigin-xOriginClientSection)/2)+ xOriginClientSection;
	//TODO revisar este switch horrible, lo fui armando mientras testeaba como se veia
	int yOffset;;
	switch(clientIndex){
		case 0:
			yOffset = (yOrigin/2);
			break;
		case 1:
			yOffset = (yOrigin*3/2);
			break;
		case 2:
			yOffset = (yOrigin*3/4);
			xOffset = -xOriginClientSection+((xOrigin-xOriginClientSection)*3);
			break;
		case 3:
			yOffset = (yOrigin/2);
			xOffset = -(((xOrigin-xOriginClientSection)*3/2)+ xOriginClientSection);

			break;
	}
	pair<int,int> initialOffset;
	initialOffset.first= -(xOffset*this->gameSettings->getTileSize());
	initialOffset.second= -(yOffset*this->gameSettings->getTileSize());

	//Creo los personajes del cliente
	xOrigin += dimension.first;
	for(int actualCharacters = 0; actualCharacters<DefaultSettings::getQtyInitialCharacters(); ++actualCharacters){
		//TODO revisar que le ponemos en tipo
		pair<int,int> positionOfProtagonista = this->mapa->getAvailablePosition(xOrigin,yOrigin);
		EntidadDinamica* protagonista = new EntidadDinamica(gameSettings->getTipoProtagonista(),
															gameSettings->getVelocidadPersonaje(),
															positionOfProtagonista.first,
															positionOfProtagonista.second,
															gameSettings->getProtagonistaPixelDimension(),
															gameSettings->getProtagonistaPixelDimension());

		protagonista->setOwner(owner);
		protagonista->setVisibilityRange(gameSettings->getRangeVisibility());
		this->protagonistas.insert(make_pair(protagonista->getId(),protagonista));
		//defino una lista con los nuevos protagonistas para que se enteren los clientes anterores
		this->newProtagonistas.push_back(protagonista);
	}
	return initialOffset;
}

Mapa* Juego::getMap(){
	return this->mapa;
}

map<int,EntidadDinamica*>* Juego::getDinamicEntities(){
	return &this->protagonistas;
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

void Juego::setTargetTo(int entityId,int target){

}

EntidadDinamica* Juego::getDinamicEntityById(int id){
	for(map<int,EntidadDinamica*>::iterator it = this->protagonistas.begin(); it != this->protagonistas.end();++it){
		if( (*it).second->getId() == id )
			return (*it).second;
	}
	return NULL;
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
