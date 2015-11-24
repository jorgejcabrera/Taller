/*
 * GameController.cpp
 *
 *  Created on: Sep 11, 2015
 *      Author: juan
 */

#include "../../Headers/Control/GameController.h"

GameController::GameController(string gameSelected){
	if(gameSelected == "CAPTURE_FLAG"){
		this->gameType = CAPTURE_FLAG;
	}else if(gameSelected == "REGICIDE"){
		this->gameType = REGICIDE;
	}else{
		this->gameType = CIVIC_CENTER;
	}

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
		listaDeTiles.push_back(it->second->getMessage());
	}
	return listaDeTiles;
}

list<Message*> GameController::getEntitiesMessages(){
	list<Message*> listaDeEntities;
	list<EntidadPartida*>* entidades = this->getJuego()->getMap()->getEntities();
	for(list<EntidadPartida*>::iterator it = entidades->begin(); it!=entidades->end();++it){
		//TODO revisar, las entidades tambien van a pertener a un cliente con lo cual tambien deberiamos mandar si el dueño está conectado o no. Seteo el ultimo parametro en 0 para simular que el dueño está conectado		
		listaDeEntities.push_back((*it)->getMessage());

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
	map<int,EntidadDinamica*>* listaPersonajes = this->juego->getDinamicEntities();
	for(map<int,EntidadDinamica*>::iterator it = listaPersonajes->begin(); it!=listaPersonajes->end();++it){
		EntidadDinamica* entidad = (*it).second;
		//pongo la posicion anterior desocupada
		pair<int,int> firstPosition = entidad->getPosition();
		this->juego->getMap()->getTileAt(firstPosition.first,firstPosition.second)->changeStatusAvailable();
		(*it).second->nextPosition();
		//pongo la nueva posicion como ocupada
		pair<int,int> newPos = entidad->getPosition();
		this->juego->getMap()->getTileAt(newPos.first,newPos.second)->changeStatusAvailable();
		//si mi destino esta ocupado, recalculo la posicion
		if (entidad->isMoving()) {
			pair<int,int> finalPos = entidad->getPositionToGo();
			pair<int,int> nextPos = entidad->getNextPosition();
			if ( !this->juego->getMap()->getTileAt(nextPos.first,nextPos.second)->isAvailable())
				this->juego->setPlaceToGo(entidad,finalPos.first,finalPos.second);
		}
	}
}

void GameController::pursuitAndAttackTarget(EntidadDinamica* attacker){
	//el target está vivo, pero no está cerca, entonces lo debemos perseguir
	if(!this->readyToInteract(attacker) ){
		pair<int,int> targetPosition = this->juego->getNearestPosition(attacker->getTarget());
		this->juego->setPlaceToGo(attacker,targetPosition.first, targetPosition.second);

	//el target está vivo pero se escapo
	}else if( this->targetOutOfReach(attacker) ){
		attacker->setTarget(0);
		attacker->prepareToInteract(false);

	//atacamos o recolectamos el recurso
	}else{
		this->attackOrWork(attacker);
	}
}

void GameController::attackOrWork(EntidadDinamica* entity){
	EntidadPartida* target = entity->getTarget();
	//si el target es un recurso, solo lo pueden recolectar los aldeanos
	if( (target->getName() == "gold" || target->getName() == "food" || target->getName() == "wood" || target->getName() == "rock") && entity->getName() != "aldeano"){
		entity->setTarget(0);
		entity->prepareToInteract(false);
		return;

	//interactuamos y colocamos el target en la lista de novedades
	}else{
		entity->attackTo();
		if(target->getHealth()>0 && target->getOwner() != ""){
			this->juego->addNewEntity(target);
		}
	}
}

void GameController::buildTarget(EntidadDinamica* builder){
	//si el target no está cerca, entonces me tengo que acercar
	if(!this->readyToInteract(builder) ){
		EntidadPartida* building = builder->getTarget();
		pair<int,int> targetPosition = this->juego->getNearestPosition(building);
		this->juego->setPlaceToGo(builder,targetPosition.first, targetPosition.second);

	//el target ya esta construido en su totalidad
	}else if( this->targetCompleted(builder) ){
		builder->setTarget(NULL);
		builder->prepareToInteract(false);
		this->juego->addNewEntity(builder);

	//construimos
	}else{
		EntidadPartida* building = builder->getTarget();
		builder->construct(building);
		this->juego->addNewEntity(building);
	}
}

void GameController::interactWithTargets(){
	map<int,EntidadDinamica*>* entities = this->juego->getDinamicEntities();
	for(map<int,EntidadDinamica*>::iterator it = entities->begin(); it != entities->end();++it ){
		if( it->second->getTarget() != 0 /*&& this->targetIsAlive(it->second)*/ ){
			//ataco o recolecto, dependiento del target
			if( it->second->getTarget()->getOwner() != it->second->getOwner()){
				this->pursuitAndAttackTarget(it->second);

			//construyo
			}else{
				this->buildTarget(it->second);
			}
		}
	}
}

//TODO la distancia minima para poder atacar depende del tipo de entidad, so deshardcodear el 1
bool GameController::readyToInteract(EntidadDinamica* entity){
	EntidadPartida* target = entity->getTarget();
	if( entity->isReadyToInteract() && target ){
		list<pair<int,int> > nearestPositions = this->juego->getEntityById(entity->getTarget()->getId())->getNearestPositions();
		for(list<pair<int,int> >::iterator it = nearestPositions.begin(); it != nearestPositions.end();++it){
			if( UtilsController::GetInstance()->getDistance(*it,entity->getPosition()) <= 1 ){
				return true;
			}
		}
	}
	return false;
}

bool GameController::targetOutOfReach(EntidadDinamica* entity){
	if(entity->getTarget()){
		pair<int,int> targetPosition = this->juego->getEntityById(entity->getTarget()->getId())->getPosition();
		return UtilsController::GetInstance()->getDistance(targetPosition,entity->getPosition()) >= 10;
	}else{
		return false;
	}
}

bool GameController::targetCompleted(EntidadDinamica* entity){
	EntidadPartida* target = entity->getTarget();
	if( target->isMaxHealth() && !target->isConstructionCompleted()){
		target->completeConstruction();
		this->juego->addNewEntity(target);
	}
	return target->isMaxHealth();
}

void GameController::updateGame(){
	this->interactWithTargets();
	this->setNextPaths();
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
