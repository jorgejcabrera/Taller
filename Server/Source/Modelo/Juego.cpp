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
	string nombre = DefaultSettings::getNameCivicCenter();
	pair<int,int> dimension = this->gameSettings->getConfigDimensionOfEntity(nombre);
	int xOrigin =  xOriginClientSection+width/4;
	int yOrigin =  yOriginClientSection+height/4;

	EntidadPartida* edificioCreado = new EntidadEstatica(nombre,dimension.first,dimension.second,true);
	edificioCreado->setPosition(xOrigin,yOrigin);
	edificioCreado->setOwner(owner);
	this->mapa->pushEntity(edificioCreado);
	this->newEntities.push_back(edificioCreado);

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
	int villagerHealth = 100;
	int villagerStrength = 4;
	float villagerPrecition = 0.5;
	for(int actualCharacters = 0; actualCharacters<DefaultSettings::getQtyInitialCharacters(); ++actualCharacters){
		//TODO revisar que le ponemos en tipo
		pair<int,int> positionOfProtagonista = this->mapa->getAvailablePosition(xOrigin,yOrigin);
		EntidadDinamica* protagonista = new EntidadDinamica(gameSettings->getTipoProtagonista(),
															gameSettings->getVelocidadPersonaje(),
															positionOfProtagonista.first,
															positionOfProtagonista.second,
															gameSettings->getProtagonistaPixelDimension(),
															gameSettings->getProtagonistaPixelDimension());
		protagonista->setHealth(villagerHealth);
		protagonista->setStrength(villagerStrength);
		protagonista->setPrecision(villagerPrecition);
		protagonista->setOwner(owner);
		protagonista->setVisibilityRange(gameSettings->getRangeVisibility());
		this->protagonistas.insert(make_pair(protagonista->getId(),protagonista));
		this->newEntities.push_back(protagonista);
	}
	return initialOffset;
}

Mapa* Juego::getMap(){
	return this->mapa;
}

map<int,EntidadDinamica*>* Juego::getDinamicEntities(){
	return &this->protagonistas;
}

list<EntidadPartida*>* Juego::getNewEntitiesToNotify(){
	return &this->newEntities;
}

void Juego::cleanNewEntities(){
	this->newEntities.clear();
}

void Juego::setPlaceToGo(int idProtagonista, int x,int y){
	EntidadDinamica* protagonistaToUpdate = this->protagonistas.at(idProtagonista);
	PathFinder* pathF = new PathFinder(protagonistaToUpdate->getPosition().first,
									  protagonistaToUpdate->getPosition().second,
									  x,y,this->mapa,this->resourseManager);

	//calculo el camino minimo para llegar a destino
	list<pair<int,int> >* caminoMinimo = pathF->buscarCamino();
	delete pathF;
	protagonistaToUpdate->setPath(caminoMinimo);
	protagonistaToUpdate->setPathIsNew(true);
}

void Juego::setTargetTo(int entityId,int target){
	EntidadDinamica* entityToUpdate = this->protagonistas.at(entityId);
	entityToUpdate->setTarget(target);
	entityToUpdate->setTargetPosition(make_pair(0,0));
}

//TODO OJO el atacante que tenia seteada a la entidad caida como target debe clenearlo sino rompe todo
list<EntidadDinamica> Juego::getFallenEntities(){
	list<EntidadDinamica> fallenEntities;
	for(map<int,EntidadDinamica*>::iterator it = this->protagonistas.begin(); it != this->protagonistas.end(); ++it){
		if(it->second->getHealth() <= 0 ){
			fallenEntities.push_front(*it->second);
			this->protagonistas.erase(it);
		}
	}
	return fallenEntities;
}

void Juego::deleteEntity(int id){
	for(map<int,EntidadDinamica*>::iterator it = this->protagonistas.begin(); it != this->protagonistas.end(); ++it){
		if(it->second->getId() == id){
			//Borro el personaje y libero el tile
			pair<int,int> position= it->second->getPosition();
			this->getMap()->getTileAt(position.first,position.second)->changeStatusAvailable();
			this->protagonistas.erase(it);
		}
	}
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

void Juego::createKingForClient(string owner){
	pair<int,int> civicCenterPosition = this->getCivicCenterPositionOfClient(owner);
	pair<int,int> positionOfProtagonista = this->mapa->getAvailablePosition(civicCenterPosition.first+4,civicCenterPosition.second+4);
	string name = "king";
	EntidadDinamica* king = new EntidadDinamica(name,
												gameSettings->getValueForAttributeOfEntity(name, "velocidad"),
												positionOfProtagonista.first,
												positionOfProtagonista.second,
												gameSettings->getValueForAttributeOfEntity(name, "pixels_dimension"),
												gameSettings->getValueForAttributeOfEntity(name, "pixels_dimension"));
	king->setHealth(100);
	king->setStrength(0);
	king->setPrecision(0);
	king->setOwner(owner);
	king->setVisibilityRange(gameSettings->getRangeVisibility());
	this->protagonistas.insert(make_pair(king->getId(),king));
	this->newEntities.push_back(king);
}

void Juego::createFlag(string owner){
	string name = "flag";
	pair<int,int> civicCenterPosition = this->getCivicCenterPositionOfClient(owner);
	pair<int,int> position = this->mapa->getAvailablePosition(civicCenterPosition.first+5,civicCenterPosition.second+5);
	pair<int,int> dimension = this->gameSettings->getConfigDimensionOfEntity(name);
	EntidadPartida* flagEntity = new EntidadEstatica(name,dimension.first,dimension.second,true);
	flagEntity->setPosition(position.first, position.second);
	flagEntity->setOwner(owner);
	this->mapa->pushEntity(flagEntity);
	this->newEntities.push_back(flagEntity);
}

pair<int,int> Juego::getCivicCenterPositionOfClient(string owner){
	list<EntidadPartida*>* listEntities = this->getMap()->getEntities();
	for(list<EntidadPartida*>::iterator iterateEntities= listEntities->begin(); iterateEntities!=listEntities->end();++iterateEntities){
		if(((*iterateEntities)->getOwner()==owner) && (*iterateEntities)->getName()==DefaultSettings::getNameCivicCenter()){
			return (*iterateEntities)->getPosition();
		}
	}
}

Juego::~Juego() {
	for(map<int,EntidadDinamica*>::iterator it=this->protagonistas.begin(); it!=this->protagonistas.end(); ++it){
			delete(it->second);
	}
	delete(this->mapa);
	this->mapa = NULL;
	this->gameSettings=NULL;
}
