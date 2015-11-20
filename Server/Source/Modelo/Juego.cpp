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
}

pair<int,int> Juego::createEntitiesForClient(string owner, int clientIndex){

	int widthMap = this->gameSettings->getMapWidth();
	int heightMap = this->gameSettings->getMapHeight();
	int xOriginClientSection;
	int yOriginClientSection;
	switch(clientIndex){
		case 0:
			xOriginClientSection = 0;
			yOriginClientSection = 0;
			break;
		case 1:
			xOriginClientSection = (widthMap/2);
			yOriginClientSection = 0;
			break;
		case 2:
			xOriginClientSection = (widthMap/2);
			yOriginClientSection = (heightMap/2);
			break;
		case 3:
			xOriginClientSection = 0;
			yOriginClientSection = (heightMap/2);
			break;
	}

	//Creo el centro civico del jugador
	string nombre = DefaultSettings::getNameCivicCenter();
	int width = this->gameSettings->getConfigAttributeOfEntityAsInt(nombre, "ancho_base");
	int height = this->gameSettings->getConfigAttributeOfEntityAsInt(nombre, "alto_base");


	int xOrigin =  xOriginClientSection+widthMap/4;
	int yOrigin =  yOriginClientSection+heightMap/4;

	EntidadPartida* edificioCreado = new EntidadEstatica(nombre,width,height,true);
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
	xOrigin += width;
	int villagerStrength = 4;
	float villagerPrecition = 0.5;
	for(int actualCharacters = 0; actualCharacters<DefaultSettings::getQtyInitialCharacters(); ++actualCharacters){
		//TODO el metodo getAvailablePosition no es redundante hay q usar get nearest position
		//pair<int,int> positionOfProtagonista = this->mapa->getAvailablePosition(xOrigin,yOrigin);
		pair<int,int> positionOfProtagonista = this->getNearestPosition(edificioCreado);
		string name = "aldeano";
		EntidadDinamica* protagonista = new EntidadDinamica(name,
															gameSettings->getConfigAttributeOfEntityAsInt(name, "velocidad"),
															positionOfProtagonista.first,
															positionOfProtagonista.second,
															gameSettings->getConfigAttributeOfEntityAsInt(name, "pixels_dimension"),
															gameSettings->getConfigAttributeOfEntityAsInt(name, "pixels_dimension"));
		protagonista->setStrength(villagerStrength);
		protagonista->setPrecision(villagerPrecition);
		protagonista->setOwner(owner);
		protagonista->setVisibilityRange(gameSettings->getRangeVisibility());
		protagonista->setBuilderEffort(gameSettings->getConfigAttributeOfEntityAsInt(name, "builder_effort"));
		protagonista->setNotifiable(true);
		this->protagonistas.insert(make_pair(protagonista->getId(),protagonista));
		this->mapa->getTileAt(positionOfProtagonista.first,positionOfProtagonista.second)->changeStatusAvailable();
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

void Juego::addNewEntity(EntidadPartida* entity){
	this->newEntities.push_back(entity);
}

void Juego::cleanNewEntities(){
	this->newEntities.clear();
}

void Juego::setPlaceToGo(int idProtagonista, int x,int y){
	EntidadDinamica* protagonistaToUpdate = this->protagonistas.at(idProtagonista);
	PathFinder* pathF = new PathFinder(protagonistaToUpdate->getPosition().first,
									  protagonistaToUpdate->getPosition().second,
									  x,y,this->mapa);

	//calculo el camino minimo para llegar a destino
	list<pair<int,int> >* caminoMinimo = pathF->buscarCamino();
	delete pathF;
	protagonistaToUpdate->setPath(caminoMinimo);
	protagonistaToUpdate->setPathIsNew(true);

	//pongo la posicion anterior desocupada
	pair<int,int> firstPosition = protagonistaToUpdate->getPosition();
	this->mapa->getTileAt(firstPosition.first,firstPosition.second)->changeStatusAvailable();
	protagonistaToUpdate->nextPosition();
	//pongo la nueva posicion como ocupada
	pair<int,int> newPos = protagonistaToUpdate->getPosition();
	this->mapa->getTileAt(newPos.first,newPos.second)->changeStatusAvailable();

}

list<EntidadPartida> Juego::getFallenEntities(){
	list<EntidadPartida> fallenEntities;
	//personajes eliminados
	for(map<int,EntidadDinamica*>::iterator it = this->protagonistas.begin(); it != this->protagonistas.end(); ++it){
		if( it->second->getHealth() <= 0 ){
			pair<int,int> position = it->second->getPosition();
			this->getMap()->getTileAt(position.first,position.second)->changeStatusAvailable();
			fallenEntities.push_front(*it->second);
			this->protagonistas.erase(it);
		}
	}
	//edificios destruidos
	for(list<EntidadPartida*>::iterator itBuilds = this->mapa->getEntities()->begin(); itBuilds != this->mapa->getEntities()->end(); ){
		if( (*itBuilds)->getHealth() <= 0 ){
			this->enableTiles(*itBuilds);
			fallenEntities.push_front(*(*itBuilds));
			delete *itBuilds;
			itBuilds = this->mapa->getEntities()->erase(itBuilds);
		}else{
			++itBuilds;
		}
	}
	//recursos consumidos
	for(list<Resource*>::iterator itResources = this->mapa->getResources()->begin(); itResources != this->mapa->getResources()->end(); ){
		if( (*itResources)->getHealth() <= 0 ){
			this->enableTiles(*itResources);
			fallenEntities.push_front(*(*itResources));
			delete *itResources;
			itResources = this->mapa->getResources()->erase(itResources);
		}else{
			++itResources;
		}
	}
	return fallenEntities;
}

void Juego::enableTiles(EntidadPartida* entity){
	pair<int,int> position = entity->getPosition();
	for(int i = position.first; i < position.first + entity->getWidth(); i++){
		for(int j= position.second; j < position.second + entity->getLength(); j++){
			this->getMap()->getTileAt(i,j)->changeStatusAvailable();
		}
	}
}

void Juego::deleteEntity(int id){
	for(map<int,EntidadDinamica*>::iterator it = this->protagonistas.begin(); it != this->protagonistas.end(); ++it){
		if(it->second->getId() == id){
			//Borro el personaje y libero el tile
			pair<int,int> position = it->second->getPosition();
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

EntidadPartida* Juego::getEntityById(int id){
	for(map<int,EntidadDinamica*>::iterator it = this->protagonistas.begin(); it != this->protagonistas.end();++it){
		if( (*it).second->getId() == id )
			return (*it).second;
	}
	list<EntidadPartida*>* entities = this->mapa->getEntities();
	for(list<EntidadPartida*>::iterator iterateEntities = entities->begin(); iterateEntities!=entities->end();++iterateEntities){
		if((*iterateEntities)->getId() == id) 
			return (*iterateEntities);
	}
	for(list<Resource*>::iterator itResources = this->mapa->getResources()->begin(); itResources!= this->mapa->getResources()->end();++itResources){
		if((*itResources)->getId() == id)
			return (*itResources);
	}
	return NULL;
}

void Juego::createNewEntitie(string owner,string type, int idOfCreator) {
	EntidadPartida* building = this->getEntityById(idOfCreator);
	pair<int, int> positionOfCreated = this->getNearestPosition(building);
	if (positionOfCreated.first == -1) positionOfCreated = this->mapa->getAvailablePosition();
	EntidadDinamica* dinamicEntity = new EntidadDinamica(type,
														gameSettings->getConfigAttributeOfEntityAsInt(type, "velocidad"),
														positionOfCreated.first,
														positionOfCreated.second,
														gameSettings->getConfigAttributeOfEntityAsInt(type, "pixels_dimension"),
														gameSettings->getConfigAttributeOfEntityAsInt(type, "pixels_dimension"));
	dinamicEntity->setStrength(gameSettings->getConfigAttributeOfEntityAsInt(type, "strength"));
	dinamicEntity->setPrecision(0.5);
	dinamicEntity->setOwner(owner);
	dinamicEntity->setVisibilityRange(gameSettings->getRangeVisibility());
	this->protagonistas.insert(make_pair(dinamicEntity->getId(),dinamicEntity));
	this->mapa->getTileAt(positionOfCreated.first,positionOfCreated.second)->changeStatusAvailable();
	this->newEntities.push_back(dinamicEntity);
}


void Juego::createKingForClient(string owner){
	pair<int,int> civicCenterPosition = this->getCivicCenterPositionOfClient(owner);
	pair<int,int> positionOfProtagonista = this->mapa->getAvailablePosition(civicCenterPosition.first+4,civicCenterPosition.second+4);
	string name = "king";
	EntidadDinamica* king = new EntidadDinamica(name,
												gameSettings->getConfigAttributeOfEntityAsInt(name, "velocidad"),
												positionOfProtagonista.first,
												positionOfProtagonista.second,
												gameSettings->getConfigAttributeOfEntityAsInt(name, "pixels_dimension"),
												gameSettings->getConfigAttributeOfEntityAsInt(name, "pixels_dimension"));
	king->setStrength(gameSettings->getConfigAttributeOfEntityAsInt(name, "strength"));
	king->setPrecision(0);
	king->setOwner(owner);
	king->setVisibilityRange(gameSettings->getRangeVisibility());
	king->setBuilderEffort(gameSettings->getConfigAttributeOfEntityAsInt(name, "builder_effort"));
	this->protagonistas.insert(make_pair(king->getId(),king));
	this->mapa->getTileAt(positionOfProtagonista.first,positionOfProtagonista.second)->changeStatusAvailable();
	this->newEntities.push_back(king);
}

void Juego::createFlag(string owner){
	string name = "flag";
	pair<int,int> civicCenterPosition = this->getCivicCenterPositionOfClient(owner);
	pair<int,int> position = this->mapa->getAvailablePosition(civicCenterPosition.first+3,civicCenterPosition.second+3);
	int width = this->gameSettings->getConfigAttributeOfEntityAsInt(name, "ancho_base");
	int height = this->gameSettings->getConfigAttributeOfEntityAsInt(name, "alto_base");
	EntidadPartida* flagEntity = new EntidadEstatica(name,width,height,true);
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
	return pair<int,int>();
}

pair<int,int> Juego::getNearestPosition(EntidadPartida* entity) {
	if (entity == NULL) return make_pair(-1,-1);
	/*pair<int,int> candidatePosition;

	list<pair<int,int> > nearesPositions = entity->getNearestPositions();
	for(list<pair<int,int> >::iterator it = nearesPositions.begin(); it!= nearesPositions.end();++it){
		stringstream ss;
		ss.str("");
		ss << "vamos a construir la entidad "<< entity->getName() << " en "<< entity->getPosition().first<< " "<< entity->getPosition().second<< " alto "<<entity->getLength()<<" ancho "<<entity->getWidth();
		Logger::get()->logDebug("Juego","getNearesPosition",ss.str());
		ss.str("");
		ss << "la primer posicion cercada es "<< (*it).first <<" "<< (*it).second;
		Logger::get()->logDebug("Juego","getNearesPosition",ss.str());
		Tile* tile = this->mapa->getTileAt((*it).first, (*it).second );
		if ( tile && tile->isAvailable())
			ss.str("");
			ss << "devolvemos la posicion " << (*it).first<< " "<< (*it).second;
			Logger::get()->logDebug("Juego","getNearesPosition",ss.str());
			return *it;
	}*/
	
	int entityWidth = gameSettings->getConfigAttributeOfEntityAsInt(entity->getName(), "ancho_base");
	int entityHeight = gameSettings->getConfigAttributeOfEntityAsInt(entity->getName(), "alto_base");

	pair<int,int> entityPosition = entity->getPosition();
	pair<int,int> candidatePosition;

	//posicion cercana al edificio
	candidatePosition = make_pair(entity->getPosition().first + entityWidth,entity->getPosition().second);
	for(; candidatePosition.second <= entityPosition.second + entityHeight ; candidatePosition.second++){
		Tile* tile = this->mapa->getTileAt(candidatePosition.first, candidatePosition.second );
		if (tile && tile->isAvailable())
			return candidatePosition;
	}

	candidatePosition = make_pair(entity->getPosition().first,entity->getPosition().second + entityHeight);
	for(; candidatePosition.first <= entityPosition.first + entityWidth ; candidatePosition.first++){
		Tile* tile = this->mapa->getTileAt(candidatePosition.first, candidatePosition.second );
		if (tile && tile->isAvailable())
			return candidatePosition;
	}

	candidatePosition = make_pair(entity->getPosition().first,entity->getPosition().second-1);
	for(; candidatePosition.first <= entityPosition.first + entityWidth ; candidatePosition.first++){
		Tile* tile = this->mapa->getTileAt(candidatePosition.first, candidatePosition.second );
		if (tile && tile->isAvailable())
			return candidatePosition;
	}

	candidatePosition = make_pair(entity->getPosition().first-1,entity->getPosition().second);
	for(; candidatePosition.second <= entityPosition.second + entityHeight ; candidatePosition.second++){
		Tile* tile = this->mapa->getTileAt(candidatePosition.first, candidatePosition.second );
		if (tile && tile->isAvailable())
			return candidatePosition;
	}
	//return this->getMap()->getAvailablePosition(entityPosition.first+entityWidth,entityPosition.second+entityHeight);
	return entity->getPosition();
	//return entity->getPosition();
}

void Juego::transferEntitiesToUser(string userFrom, string userTo){
	stringstream ss;
	ss<< "Entre en  transferEntitiesToUser "<< userFrom << " to "<< userTo;
	Logger::get()->logInfo("Juego","transferEntitiesToUser",ss.str());
	for(map<int,EntidadDinamica*>::iterator it = this->protagonistas.begin(); it != this->protagonistas.end();++it){
		if( it->second->getOwner() == userFrom ){
			it->second->setOwner(userTo);
			this->newEntities.push_back(it->second);
		}
	}
	list<EntidadPartida*>* entities = this->mapa->getEntities();
	for(list<EntidadPartida*>::iterator iterateEntities = entities->begin(); iterateEntities!=entities->end();++iterateEntities){
		if((*iterateEntities)->getOwner() == userFrom && (*iterateEntities)->getName()!="flag"){
			(*iterateEntities)->setOwner(userTo);
			this->newEntities.push_back((*iterateEntities));
		}
	}
}

int Juego::buildEntity(string nameEntity, int positionX, int positionY, string owner){
	int width = this->gameSettings->getConfigAttributeOfEntityAsInt(nameEntity, "ancho_base");
	int height = this->gameSettings->getConfigAttributeOfEntityAsInt(nameEntity, "alto_base");
	EntidadPartida* flagEntity = new EntidadEstatica(nameEntity,width,height,false);
	flagEntity->setPosition(positionX, positionY);
	flagEntity->setOwner(owner);
	flagEntity->setHealth(1);
	this->mapa->pushEntity(flagEntity);
	this->newEntities.push_back(flagEntity);
	return flagEntity->getId();
}

Juego::~Juego() {
	for(map<int,EntidadDinamica*>::iterator it=this->protagonistas.begin(); it!=this->protagonistas.end(); ++it){
			delete(it->second);
	}
	delete(this->mapa);
	this->mapa = NULL;
	this->gameSettings=NULL;
}
