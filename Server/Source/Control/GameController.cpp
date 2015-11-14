/*
 * GameController.cpp
 *
 *  Created on: Sep 11, 2015
 *      Author: juan
 */

#include "../../Headers/Control/GameController.h"

GameController::GameController(){
	//this->gameType = CIVIC_CENTER;
	//this->gameType = REGICIDE;
	this->gameType = CAPTURE_FLAG;
	this->gameSettings = GameSettings::GetInstance();
	this->utils = UtilsController::GetInstance();
	this->gameRunning = true;
	this->juego = new Juego();
	this->runCycles = 0;
	this->maxFramesPerSecond = 50; // maxima cantidad de frames del juego principal
}

Juego* GameController::getJuego(){
	return this->juego;
}

bool GameController::isGameRunning(){
	return this->gameRunning;
}

void GameController::gameFinished(){
	this->gameRunning=false;
}

list<Message*> GameController::getTilesMessages(){
	list<Message*> listaDeTiles;
	map<pair<int,int>,Tile*>* tilesList = this->juego->getMap()->getTiles();
	for(map<pair<int,int>,Tile*>::iterator it=tilesList->begin(); it!=tilesList->end(); ++it){
		Message* tileMessage = new Message(0,"tile");
		tileMessage->setName(it->second->getSuperficie());
		tileMessage->setPosition(it->first);
		listaDeTiles.push_back(tileMessage);
	}
	return listaDeTiles;
}

list<Message*> GameController::getEntitiesMessages(){
	list<Message*> listaDeEntities;
	list<EntidadPartida*>* entidades = this->getJuego()->getMap()->getEntities();
	for(list<EntidadPartida*>::iterator it=entidades->begin(); it!=entidades->end();++it){
		string tipoEntidad = DefaultSettings::getTypeEntity((*it)->getName());
		//TODO revisar, las entidades tambien van a pertener a un cliente con lo cual tambien deberiamos mandar si el dueño está conectado o no. Seteo el ultimo parametro en 0 para simular que el dueño está conectado
		Message* entityMessage = new Message((**it).getId(), tipoEntidad);
		entityMessage->setName((*it)->getName());
		entityMessage->setPosition((*it)->getPosition());
		entityMessage->setOwner((*it)->getOwner());
		entityMessage->setHealth((*it)->getHealth());
		listaDeEntities.push_back(entityMessage);
	}
	return listaDeEntities;
}

list<int> GameController::getEntitiesOfClient(string userName){
	list<int> idOfEntities;
	map<int,EntidadDinamica*>* listaPersonajes = this->juego->getDinamicEntities();
	for(map<int,EntidadDinamica*>::iterator iteratePersonajes= listaPersonajes->begin(); iteratePersonajes!=listaPersonajes->end();++iteratePersonajes){
		if(iteratePersonajes->second->getOwner()==userName){
			idOfEntities.push_back(iteratePersonajes->first);
		}
	}
	return idOfEntities;
}

void GameController::setNextPaths(){
	//antes de setear el proximo path, me fijo si hay un recurso en donde esta
	map<int,EntidadDinamica*>* listaPersonajes = this->juego->getDinamicEntities();
	for(map<int,EntidadDinamica*>::iterator it = listaPersonajes->begin(); it!=listaPersonajes->end();++it){
		pair<int,int> pos = (*it).second->getPosition();
		if( ! (*it).second->isWalking() && this->juego->getResourceManager()->resourceAt(pos.first,pos.second)){
			this->juego->getResourceManager()->collectResourceAt(&pos);
			this->juego->getResourceManager()->setUltimoEnConsumir((*it).second->getOwner());
		}
		
		//pongo el tile anterior disponible
		pair<int,int> firstPosition = (*it).second->getPosition();
		this->juego->getMap()->getTileAt(firstPosition.first,firstPosition.second)->changeStatusAvailable();
		//busco la nueva posicion
		(*it).second->nextPosition();
		//pongo el nuevo tile como ocupado
		pair<int,int> newPos = (*it).second->getPosition();
		this->juego->getMap()->getTileAt(newPos.first,newPos.second)->changeStatusAvailable();

	}
}

void GameController::pursuitAndAttackTarget(){
	map<int,EntidadDinamica*>* entities = this->juego->getDinamicEntities();
	for(map<int,EntidadDinamica*>::iterator it = entities->begin(); it != entities->end();++it ){
		if( it->second->getTarget() != 0){
			if( this->targetIsAlive(it->second) && !this->readyToAttack(it->second) ){
				pair<int,int> targetPosition = this->juego->getEntityById(it->second->getTarget())->getPosition();
				this->juego->setPlaceToGo(it->second->getId(),targetPosition.first, targetPosition.second);
			
			}else if( this->targetIsAlive(it->second) && this->targetOutOfReach(it->second) ){
				this->juego->setTargetTo(it->second->getId(),0);

			}else if( this->targetIsAlive(it->second) ){
				EntidadPartida* enemy = this->juego->getEntityById(it->second->getTarget());
				it->second->attackTo(enemy);
			}
		}
	}
	return;
}

//TODO la distancia minima para poder atacar depende del tipo de entidad, so deshardcodear el 1
bool GameController::readyToAttack(EntidadDinamica* entity){
	pair<int,int> targetPosition = this->juego->getEntityById(entity->getTarget())->getPosition();
	return  UtilsController::GetInstance()->getDistance(targetPosition,entity->getPosition()) <= 1;
}

bool GameController::targetIsAlive(EntidadDinamica* entity){
	EntidadPartida* targetEntity = this->juego->getEntityById(entity->getTarget());
	if(!targetEntity){
		entity->setTarget(0);
		entity->setTargetPosition(make_pair(0,0));
		return false;
	}
	return true;
}

bool GameController::targetOutOfReach(EntidadDinamica* entity){
	pair<int,int> targetPosition = this->juego->getEntityById(entity->getTarget())->getPosition();
	return UtilsController::GetInstance()->getDistance(targetPosition,entity->getPosition()) >= 10;
}

void GameController::updateGame(){
	this->pursuitAndAttackTarget();
	this->setNextPaths();
	this->juego->getResourceManager()->actualizar();
}

int GameController::getRunCycles(){
	return this->runCycles;
}

int GameController::getMaxFramesPerSecond(){
	return this->maxFramesPerSecond;
}

void GameController::delay(){
	this->runCycles++;
	SDL_Delay(50); // para que sean 50 frames x segundos
}

void GameController::delay(int ms){
	this->runCycles++;
	SDL_Delay(ms);
}

bool GameController::checkIfClientLostGame(string clientName){
	bool lost=false;
	switch(this->gameType){
		case CIVIC_CENTER:
			lost=(!this->isCivicCenterStillExist(clientName));
			break;
		case CAPTURE_FLAG:
			lost=(!this->clientKeepFlag(clientName));
			lost=false;
			break;
		case REGICIDE:
			lost=(!this->isKingOfClientAlive(clientName));
			break;
	}
	return lost;
}

bool GameController::isCivicCenterStillExist(string userName){
	list<EntidadPartida*>* listEntities = this->juego->getMap()->getEntities();
	for(list<EntidadPartida*>::iterator iterateEntities= listEntities->begin(); iterateEntities!=listEntities->end();++iterateEntities){
		if(((*iterateEntities)->getOwner()==userName) && (*iterateEntities)->getName()==DefaultSettings::getNameCivicCenter()){
			return true;
		}
	}
	return false;
}

bool GameController::clientKeepFlag(string userName){
	list<EntidadPartida*>* listEntities = this->juego->getMap()->getEntities();
	for(list<EntidadPartida*>::iterator iterateEntities= listEntities->begin(); iterateEntities!=listEntities->end();++iterateEntities){
		if(((*iterateEntities)->getOwner()==userName) && (*iterateEntities)->getName()== "flag"){
			return true;
		}
	}
	return false;
}

bool GameController::isKingOfClientAlive(string userName){
	map<int,EntidadDinamica*>* listaPersonajes = this->juego->getDinamicEntities();
	for(map<int,EntidadDinamica*>::iterator iteratePersonajes= listaPersonajes->begin(); iteratePersonajes!=listaPersonajes->end();++iteratePersonajes){
		//TODO ver de crear una entidad con el name king
		if((iteratePersonajes->second->getOwner()==userName) && iteratePersonajes->second->getName()=="king"){
			return true;
		}
	}
	return false;
}

pair<int,int> GameController::createEntitiesForClient(string owner, int clientIndex){
	pair<int,int> offsetClient = this->getJuego()->createEntitiesForClient(owner,clientIndex);
	if(this->gameType == REGICIDE){
		this->getJuego()->createKingForClient(owner);
	}else if(this->gameType == CAPTURE_FLAG){
		this->getJuego()->createFlag(owner);
	}
	return offsetClient;
}

GameController::~GameController() {
	//No ejecuto el destructor de juego porque lo hace el juegoVista
	this->juego=NULL;
//	this->utils->~UtilsController();
	delete(this->utils);
	this->utils = NULL;
//	this->gameSettings->~GameSettings();
	delete(this->gameSettings);
	this->gameSettings = NULL;
}
