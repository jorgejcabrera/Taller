/*
 * GameController.cpp
 *
 *  Created on: Sep 11, 2015
 *      Author: juan
 */

#include "../../Headers/Control/GameController.h"

GameController::GameController(){
	this->gameSettings = GameSettings::GetInstance();
	this->utils = UtilsController::GetInstance();
	this->juegoVista = new JuegoVista();
	this->event = new SDL_Event();
	this->initialPosMouseX = 0;
	this->initialPosMouseY = 0;
	this->finalPosMouseX = 0;
	this->finalPosMouseY = 0;
	this->runCycles = 0;
	this->maxFramesPerSecond = 50; // maxima cantidad de frames del juego principal
	this->gameRunning=false;
	this->gameStatus = RUNNING;
	this->pressedMouseButton = "";
	this->entityToBuild = "";
	this->mixer = Mixer::GetInstance();
}

list<Message*> GameController::getMessagesFromEvent(string userName){
	list<Message*> messages;
			while(SDL_PollEvent(event)){
				if(this->entityToBuild != ""){
					this->placeTheBuilding(this->entityToBuild);
				}

				if( event->type == SDL_QUIT){
					this->juegoVista->getMenuVista()->deselectedEntity();
					Message* message = new Message();
					msg_game body;
					body.set_id(0);
					body.set_nombre(userName);
					body.set_tipo("exit");
					message->setContent(body);
					messages.push_back(message);
					return messages;
				}
				if( event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
					pressedMouseButton = "left";
					SDL_GetMouseState(&initialPosMouseX,&initialPosMouseY);
					return messages;
				}

				if( event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_RIGHT) {
					pressedMouseButton = "right";
					SDL_GetMouseState(&initialPosMouseX,&initialPosMouseY);
					return this->action();
				}
				if( event->type == SDL_MOUSEBUTTONUP && pressedMouseButton == "left"){
					if(this->entityToBuild != ""){
						this->entityToBuild = "";
						this->juegoVista->clearAllDataForBuilding();
					}
					this->entitiesSelected.clear();
					this->juegoVista->getMenuVista()->deselectedEntity();
					this->selection();
				}
				if( event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_m)
					this->mixer->startOrStopMusic();
			}
	return messages;
}

void GameController::readyToAttack(list<Message*>* messages){
	map<int, EntidadDinamicaVista*>* entities = this->juegoVista->getDinamicEntities();
	for(map<int, EntidadDinamicaVista*>::iterator it = entities->begin(); it != entities->end() ;++it){
		if( it->second->getTarget() != NULL ){
			if(it->second->getName() == "cobra"){
				this->getMixer()->playCarAttack();
			}

			EntidadPartidaVista* target = it->second->getTarget();
			int distanceBeetweenTiles = 50 * target->getLength();
			pair<int,int> targetPosition = this->utils->getIsometricPosition(target->getPosition().first, target->getPosition().second);
			
			//el target se movio luego de que empezo la pelea, pero lo podemos alcanzar
			if( this->utils->getDistance(it->second->getScreenPosition(), targetPosition) > distanceBeetweenTiles && it->second->isReadyToAttack()){
				it->second->prepareToFight(false);
				Message* message = new Message();
				msg_game body;
				body.set_id(it->second->getId());
				body.set_tipo("pursuit");
				body.set_target(it->second->getTarget()->getId());
				message->setContent(body);
				messages->push_back(message);
				return;
			}

			//se envia por segunda vez el msj para que empieze a atacar cuando esta cerca del target
			if(  this->utils->getDistance(it->second->getScreenPosition(), targetPosition) < distanceBeetweenTiles && !it->second->isReadyToAttack() ){
				Message* message = new Message();
				msg_game body;
				body.set_id(it->second->getId());
				body.set_tipo("attack");
				body.set_target(target->getId());
				message->setContent(body);
				messages->push_back(message);
				it->second->prepareToFight(true);
			}
		}
	}
}

void GameController::selection() {
	if ( initialPosMouseY <= gameSettings->getScreenHeight()-gameSettings->getAlturaMenuInferior() ){

		SDL_GetMouseState(&finalPosMouseX,&finalPosMouseY);
		pair<int,int>* offset = this->juegoVista->getOffset();
		pair<int,int> cartesianPosition;
		map<string,string> entidadMap;

		for (int i = this->initialPosMouseX; i <= this->finalPosMouseX ; i = i + gameSettings->getTileSize()/2) {
			for ( int j = this->initialPosMouseY ; j <= this->finalPosMouseY ; j = j + gameSettings->getTileSize()/4) {
				cartesianPosition = this->utils->convertToCartesian(i-offset->first,j-offset->second);
				entidadMap = juegoVista->getEntityAt(cartesianPosition);
				if(entidadMap.size()>0){
					EntidadPartidaVista* entity = this->juegoVista->getEntityById(atoi(entidadMap.at("id").c_str()));
					this->entitiesSelected.push_back(entity);
				}
			}
		}
		this->entitiesSelected.sort();
		this->entitiesSelected.unique();

		if (this->entitiesSelected.size() == 1) {
			this->juegoVista->entitiesToRenderInMenu(this->entitiesSelected, this->clientName);
			if (this->entitiesSelected.back()->getOwner() != this->clientName )  this->entitiesSelected.clear();
		} else { // si tengo mas de una entidad seleccionada, solo renderizo mis dinamicas
			list<EntidadPartidaVista*>::iterator it = this->entitiesSelected.begin();
			while ( !this->entitiesSelected.empty() && it != this->entitiesSelected.end()) {
				if (this->juegoVista->getDinamicEntityById((*it)->getId()) == NULL ||
					((*it)->getOwner() != this->clientName )) it = this->entitiesSelected.erase(it);
				else ++it;
			}
			this->juegoVista->entitiesToRenderInMenu(this->entitiesSelected, this->clientName);
		}
	}
}

//TODO este método es un asco lleno de else if sin sentido, lo tenemos que refactorizar
list<Message*> GameController::action(){
	list<Message*> messages;
	if (!this->entitiesSelected.empty()) {
		if ( initialPosMouseY >= gameSettings->getScreenHeight()-gameSettings->getAlturaMenuInferior() ){
			//menu
			return this->interactiveMenu(initialPosMouseX,initialPosMouseY);
		
		}else if( this->entityToBuild != "" && this->juegoVista->isAvailablePosForBuild()){
			this->juegoVista->clearAllDataForBuilding();
			EntidadPartidaVista* entity = this->entitiesSelected.front();
			Message* message = new Message();
			msg_game body;
			body.set_id(entity->getId());
			body.set_tipo("building");
			body.set_nombre(this->entityToBuild);
			body.set_x(finalPosMouseX);
			body.set_y(finalPosMouseY);
			body.set_owner(this->clientName);
			message->setContent(body);
			messages.push_back(message);
			EntidadDinamicaVista* entityDinamic = this->juegoVista->getDinamicEntityById(entity->getId());
			entityDinamic->prepareToFight(true);
			//gasto los recursos
			this->decreaseResources(this->entityToBuild);
			this->entityToBuild = "";
		}else{
			list<EntidadPartidaVista*>::iterator it = this->entitiesSelected.begin();
			EntidadDinamicaVista* entity = this->juegoVista->getDinamicEntityById((*it)->getId());
			pair<int,int> cartesianPosition = this->getValidCartesianPosition(entity);
			map<string,string> targetToAttack = this->juegoVista->getEntityAt(cartesianPosition);

			//construir
			if( targetToAttack.size() > 0 && !this->juegoVista->getDinamicEntityById(atoi(targetToAttack["id"].c_str())) && this->clientName.compare(targetToAttack["owner"].c_str()) == 0 ){
				for (; it != this->entitiesSelected.end() ; ++it ) {
					Message* message = new Message();
					msg_game body;
					body.set_id((*it)->getId());
					body.set_tipo("build");
					body.set_target(atoi(targetToAttack["id"].c_str()));
					message->setContent(body);
					EntidadPartidaVista* target = this->juegoVista->getEntityById(atoi(targetToAttack["id"].c_str()));
					entity->setTarget(target);
					entity->prepareToFight(false);
					messages.push_back(message);
				}

			//dirigirse a atacar o consumir recurso
			}else if( targetToAttack.size() > 0 && this->clientName.compare(targetToAttack["owner"].c_str()) != 0 ){
				for (; it != this->entitiesSelected.end() ; ++it ) {
					Message* message = new Message();
					msg_game body;
					body.set_id((*it)->getId());
					body.set_tipo("go");
					body.set_target(atoi(targetToAttack["id"].c_str()));
					message->setContent(body);
					EntidadPartidaVista* target = this->juegoVista->getEntityById(atoi(targetToAttack["id"].c_str()));
					entity->setTarget(target);
					entity->prepareToFight(false);
					messages.push_back(message);
				}
			
			//update
			}else if( entity ){
				for (; it != this->entitiesSelected.end() ; ++it ) {
					Message* message = new Message();
					msg_game body;
					body.set_id((*it)->getId());
					body.set_tipo("update");
					body.set_x(cartesianPosition.first);
					body.set_y(cartesianPosition.second);
					message->setContent(body);
					messages.push_back(message);
					entity->setTarget(NULL);
					entity->prepareToFight(false);
				}
			}

		}
	}
	return messages;
}

JuegoVista* GameController::getJuegoVista(){
	return this->juegoVista;
}

void GameController::setGameRunning(){
	this->gameRunning = true;
	this->mixer->playMusic();
}

void GameController::updateGame(){
	map<int,EntidadDinamicaVista*>* entidades = this->juegoVista->getDinamicEntities();
	for(map<int,EntidadDinamicaVista*>::iterator it = entidades->begin(); it !=entidades->end(); ++it){
		this->updatePosition((*it).second->getId());
	}

	pair<int,int> offset = this->getOffset(this->juegoVista->getOffset()->first,this->juegoVista->getOffset()->second);
	juegoVista->updateOffset(offset.first,offset.second);
}

int GameController::getRunCycles(){
	return this->runCycles;
}

int GameController::getMaxFramesPerSecond(){
	return this->maxFramesPerSecond;
}

pair<int,int> GameController::getOffset(int offSetX, int offSetY){
	int posicionX = 0;
	int posicionY = 0;
	SDL_GetMouseState(&posicionX, &posicionY);

	if (posicionX >= gameSettings->getMargenDerechoUno()	&& posicionX < gameSettings->getMargenDerechoDos() && !(offSetX < gameSettings->getLimiteDerecho())) {
		offSetX -= gameSettings->getVelocidadScrollUno();
	}
	if (posicionX >= gameSettings->getMargenDerechoDos() && !(offSetX < gameSettings->getLimiteDerecho())) {
		offSetX -= 1 * gameSettings->getVelocidadScrollDos();
	}
	if ((posicionX > gameSettings->getMargenIzquierdoDos()) && (posicionX <= gameSettings->getMargenIzquierdoUno()) && !(offSetX > gameSettings->getLimiteIzquierdo())) {
		offSetX += gameSettings->getVelocidadScrollUno();
	}
	if (posicionX <= gameSettings->getMargenIzquierdoDos() && !(offSetX > gameSettings->getLimiteIzquierdo())) {
		offSetX += gameSettings->getVelocidadScrollDos();
	}
	if ((posicionY <= gameSettings->getMargenSuperiorUno()) && (posicionY > gameSettings->getMargenSuperiorDos()) && !((offSetY > gameSettings->getLimiteSuperior()))) {
		offSetY += gameSettings->getVelocidadScrollUno();
	}
	if (posicionY <= gameSettings->getMargenSuperiorDos(/*atoi(targetToAttack["id"].c_str())*/) && !((offSetY > gameSettings->getLimiteSuperior()))) {
		offSetY += gameSettings->getVelocidadScrollDos();
	}
	if (posicionY >= gameSettings->getMargenInferiorUno() && (posicionY < gameSettings->getMargenInferiorDos()) && !((offSetY < gameSettings->getLimiteInferior()))) {
		offSetY -= gameSettings->getVelocidadScrollUno();
	}
	if ((posicionY >= gameSettings->getMargenInferiorDos()) && !((offSetY < gameSettings->getLimiteInferior()))) {
		offSetY -= gameSettings->getVelocidadScrollDos();
	}
	pair<int,int> curretOffset;
	curretOffset.first = offSetX;
	curretOffset.second = offSetY;
	return curretOffset;
}

pair<int,int> GameController::getValidCartesianPosition(EntidadPartidaVista* entidad){
	if(!entidad) return make_pair(-1,-1);
	pair<int,int>* offset = this->juegoVista->getOffset();
	pair<int,int> cartesianPosition = this->utils->convertToCartesian( this->initialPosMouseX-offset->first, this->initialPosMouseY-offset->second);

	//las coordenadas cartesianas siempre tienen que quedar dentro del mapa
	if( cartesianPosition.first < 0 ){
		cartesianPosition.first = 0;
	}else if( cartesianPosition.first >= gameSettings->getMapWidth()){
		cartesianPosition.first = gameSettings->getMapWidth() - 1 ;
	}
	if( cartesianPosition.second < 0){
		cartesianPosition.second = 0;
	}else if( cartesianPosition.second >= gameSettings->getMapHeight()){
		cartesianPosition.second = gameSettings->getMapHeight() - 1;
	}

	return cartesianPosition;
}

void GameController::updatePosition(int id){
	EntidadDinamicaVista* entity = this->juegoVista->getDinamicEntityById(id);
	if( !(entity->getCamino()->empty()) && !(entity->isWalking())){
		pair<int,int> nuevaPos = entity->getCamino()->front();
		entity->getCamino()->pop_front();

		entity->setPosition(nuevaPos.first,nuevaPos.second);
		pair<int,int> destinoIsometrico = this->utils->GetInstance()->getIsometricPosition(nuevaPos.first,nuevaPos.second);
		entity->setScreenPosition(destinoIsometrico.first,destinoIsometrico.second);
	}
}

void GameController::delay(){
	this->runCycles++;
	if(this->gameRunning){
		SDL_Delay(50); // para que sean 50 frames x segundos
	}else{
		SDL_Delay(1000); // espero 1 segundo porque aun no esta en juego
	}
}

void GameController::delay(int delayMs){
	this->runCycles++;
	SDL_Delay(delayMs);
}

bool GameController::gameIsRunning(){
	return this->gameRunning;
}

void GameController::setClientName(string name){
	this->clientName = name;
}

void GameController::winGame(){
	this->gameStatus = WIN;
}

void GameController::loseGame(){
	this->gameStatus = LOSE;
}

void GameController::disconnectedGame(){
	this->gameStatus = DISCONNECTED;
}

void GameController::showFinalMessage(){
	string finalMessage= "";
	if(this->gameStatus == WIN){
		finalMessage = "Victory is yours";
	}else if(this->gameStatus == LOSE){
		finalMessage = "You Died";
	}else if (this->gameStatus == DISCONNECTED){
		finalMessage = "Server disconnected";
	}
	if(finalMessage!=""){
		this->getJuegoVista()->renderFinalMessage(finalMessage);
		this->delay(5000);
	}
}

list<Message*> GameController::interactiveMenu(int initialPosMouseX,int initialPosMouseY) {
	list<Message*> messages;
	pair<int, string> buildingAndEntitie = this->juegoVista->getMenuVista()->getTypeOfNewEntity(initialPosMouseX,initialPosMouseY);
	if (buildingAndEntitie.second != "") {
		if (this->hasResourcesRequired(buildingAndEntitie.second)) {
			if( buildingAndEntitie.second == "Castle" || buildingAndEntitie.second == "Army" || buildingAndEntitie.second=="molino"){
				this->entityToBuild = buildingAndEntitie.second;
				this->juegoVista->setEntityForBuild(this->entityToBuild);
			}else{
				//gasto los recursos
				this->decreaseResources(buildingAndEntitie.second);
				Message* message = new Message();
				msg_game body;
				body.set_id(buildingAndEntitie.first);
				body.set_tipo("create");
				body.set_nombre(buildingAndEntitie.second);
				message->setContent(body);
				message->setOwner(this->clientName);
				messages.push_back(message);

				if(buildingAndEntitie.second == "cobra"){
					this->getMixer()->playCarStart();
				}else if(buildingAndEntitie.second == "caballo"){
					this->getMixer()->playHorse();
				}
			}
		}
	}
	return messages;
}

bool GameController::hasResourcesRequired(string entity){
	ResourceCounter* resourceCounter = this->juegoVista->getResourceCounter();
	map<string,int> costs = this->gameSettings->getCostsOf(entity);
	bool hasResources = (costs["food"] <= resourceCounter->getFood() &&
					costs["rock"] <= resourceCounter->getRock() &&
					costs["gold"] <= resourceCounter->getGold() &&
					costs["wood"] <= resourceCounter->getWood());
	return hasResources;
}

void GameController::decreaseResources(string entity){
	ResourceCounter* resourceCounter = this->juegoVista->getResourceCounter();
	map<string,int> costs = this->gameSettings->getCostsOf(entity);
	for (map<string,int>::iterator it = costs.begin(); it != costs.end(); ++it){
		for (int resource = (*it).second; resource!=0 ; resource --) {
			resourceCounter->gastar((*it).first);
		}
	}
}

void GameController::placeTheBuilding(string buildingName){
	pair<int,int> mouseCartesianPosition = this->convertMousePositionToCartesianPosition();
	//me fijo si movio el mouse
	if(this->finalPosMouseX != mouseCartesianPosition.first || this->finalPosMouseY != mouseCartesianPosition.second){
		this->finalPosMouseX = mouseCartesianPosition.first;
		this->finalPosMouseY = mouseCartesianPosition.second;
		EntidadConfig* entityConfig = this->gameSettings->getEntityConfig(buildingName);
		this->juegoVista->clearTilesForBuilding();
		pair<int,int> lowerVertex = make_pair(this->finalPosMouseX+entityConfig->getAncho(), finalPosMouseY + entityConfig->getAlto());
		for(int j=finalPosMouseY; j<lowerVertex.second; j++){
			for(int i=finalPosMouseX; i<lowerVertex.first; i++){
				this->juegoVista->addTileForBuilding(i,j);
			}
		}
	}
}

pair <int,int> GameController::convertMousePositionToCartesianPosition(){
	int posicionX = 0;
	int posicionY = 0;
	SDL_GetMouseState(&posicionX, &posicionY);
	pair<int,int>* offset = this->juegoVista->getOffset();
	return this->utils->convertToCartesian( posicionX - offset->first, posicionY - offset->second);
}

Mixer* GameController::getMixer() {
	return this->mixer;
}

GameController::~GameController() {
	//delete(this->juegoVista);
	this->juegoVista=NULL;
	//	this->utils->~UtilsController();
	delete(this->utils);
	this->utils = NULL;
	//	this->gameSettings->~GameSettings();
	delete(this->gameSettings);
	this->gameSettings = NULL;
	this->event->quit;
	delete(this->event);
	this->event = NULL;
	delete(this->mixer);
	this->mixer = NULL;
}

