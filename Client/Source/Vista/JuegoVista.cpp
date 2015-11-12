/*
 * JuegoVista.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "../../Headers/Vista/JuegoVista.h"

JuegoVista::JuegoVista() {
	gameSettings = GameSettings::GetInstance();
	this->offset.first = 0;
	this->offset.second = 0;
	this->menuVista = new MenuVista();
	this->loginVista = new LoginVista();
}

MenuVista* JuegoVista::getMenuVista(){
	return this->menuVista;
}

void JuegoVista::createView(){
	picassoHelper = PicassoHelper::GetInstance(gameSettings->getScreenWidth(), gameSettings->getScreenHeight());
}

void JuegoVista::setResources(int alimento, int madera, int oro) {
//???
}

string JuegoVista::renderUserInputView(string initialMessage){
	string userInput = this->loginVista->askInfoUser(initialMessage);
	return userInput;
}

void JuegoVista::renderFinishLogin(string finalMessage){
	this->loginVista->renderFinishLogin(finalMessage);
}

void JuegoVista::render(int runCycles, ResourceCounter* resourceCounter, string userName){
	this->picassoHelper->clearView();
	this->drawIsometricMap();
	this->setFoggedTiles(userName);
	this->drawDinamicEntities(runCycles);
	this->drawStaticEntities(runCycles);
	this->drawSemiStaticsEntities(runCycles);
	this->drawFog();
	this->drawMenu();
	this->drawResources(resourceCounter);
	this->drawMiniMap();
	this->picassoHelper->renderView();
}

void JuegoVista::renderFinalMessage(string finalMessage){
	PicassoHelper::GetInstance()->renderText(GameSettings::GetInstance()->getScreenWidth()/3,GameSettings::GetInstance()->getScreenHeight()/2,finalMessage.size()*20,40,finalMessage,255,255,255);
	this->picassoHelper->renderView();
}

void JuegoVista::drawFog() {
	int posX = 0;
	int posY = 0;
	int offsetX = this->getOffset()->first;
	int offsetY = this->getOffset()->second;

	for(list<TileVista*>::iterator itTiles = this->tiles.begin(); itTiles!=this->tiles.end(); ++itTiles){
		posY = ((*itTiles)->getPosX()+(*itTiles)->getPosY()) * gameSettings->getTileSize() / 2 + offsetY;
		posX = ((*itTiles)->getPosX()-(*itTiles)->getPosY()) * gameSettings->getTileSize() + gameSettings->getScreenWidth() / 2 + offsetX;	//comienzo a dibujar de la mitad de la pantalla

		if ((*itTiles)->getSeen()){
			if ( (*itTiles)->getFogged()) {
				this->picassoHelper->renderFogOfWar(this->gameSettings->getPathOfFoggedTile(),posX,posY, gameSettings->getTileSize() * 2+2, gameSettings->getTileSize()+1);
			}
		} else {
			this->picassoHelper->renderObject(this->gameSettings->getPathOfCoveredTile(),posX,posY, gameSettings->getTileSize() * 2+2, gameSettings->getTileSize()+1);
		}
	}
}

void JuegoVista::drawMenu() {
	this->menuVista->drawMe();
}

void JuegoVista::drawIsometricMap(){
	int posX = 0;
	int posY = 0;
	int offsetX = this->getOffset()->first;
	int offsetY = this->getOffset()->second;

	for(list<TileVista*>::iterator itTiles = this->tiles.begin(); itTiles!=this->tiles.end(); ++itTiles){
		if ((*itTiles)->getSeen()){
			posY = ((*itTiles)->getPosX()+(*itTiles)->getPosY()) * gameSettings->getTileSize() / 2 + offsetY;
			posX = ((*itTiles)->getPosX()-(*itTiles)->getPosY()) * gameSettings->getTileSize() + gameSettings->getScreenWidth() / 2 + offsetX;	//comienzo a dibujar de la mitad de la pantalla
			this->picassoHelper->renderObject((*itTiles)->getPathImage(),posX,posY, gameSettings->getTileSize() * 2, gameSettings->getTileSize());
			for(map<int,EntidadEstaticaVista*>::iterator itEstaticos = this->buildings.begin(); itEstaticos!=this->buildings.end(); ++itEstaticos){
				pair<int,int>* posicionEstaticos = (*itEstaticos).second->getPosition();
				if ( ( posicionEstaticos->first == (*itTiles)->getPosX() ) && ( posicionEstaticos->second == (*itTiles)->getPosY() ) ){
					(*itEstaticos).second->saw();
				}
			}
		}
	}
}

void JuegoVista::drawStaticEntities(int runCycles){
	pair<int,int> isometricPosition;
	int offSetX = this->getOffset()->first;
	int offSetY = this->getOffset()->second;

	for(map<int,EntidadEstaticaVista*>::iterator itEstaticos = this->buildings.begin(); itEstaticos!=this->buildings.end(); ++itEstaticos){
		EntidadEstaticaVista* entidad = (*itEstaticos).second;
		if (entidad->getSeen()) {
			isometricPosition = UtilsController::GetInstance()->getIsometricPosition(entidad);
			entidad->drawMe(isometricPosition,offSetX,offSetY,runCycles);
		}
	}
}

void JuegoVista::drawDinamicEntities(int runCycles){
	pair<int,int> isometricPosition;
	EntidadDinamicaVista* entidad;
	for(map<int,EntidadDinamicaVista*>::iterator itDinamicos = this->personajes.begin(); itDinamicos!=this->personajes.end(); ++itDinamicos){
		entidad = (*itDinamicos).second;
		drawDinamicEntity(entidad,runCycles,false);
	}
}

void JuegoVista::drawDinamicEntity(EntidadDinamicaVista* entidad, int runCycles,bool isMyEntity){
	int offSetX = this->getOffset()->first;
	int offSetY = this->getOffset()->second;
	pair<int,int> screenPosition = entidad->getScreenPosition();
	entidad->trasladarse();
	bool drawEntity = true;
	//si hay una entidad para consumir la eliminamos
	int id = this->consumeResource(entidad);
	if( id != 0 ) this->deleteStaticEntityById(id);
	if(!isMyEntity){
		drawEntity = isEnemyEntityVisible(*(entidad->getPosition()));
	}
	if(drawEntity){
		this->picassoHelper->renderObject(	entidad->getPathImage(),
											screenPosition.first - entidad->getWidthPixel()/2 + offSetX,
											screenPosition.second  - entidad->getLengthPixel()/2 + offSetY,
											gameSettings->getTileSize(),
											gameSettings->getTileSize(),
											entidad->getPositionOfSprite(runCycles));
	}
}

void JuegoVista::drawSemiStaticsEntities(int runCycles){
	pair<int,int> isometricPosition;
	for(map<int,EntidadSemiEstaticaVista*>::iterator itSemiStatics = this->semiEstaticos.begin(); itSemiStatics!=this->semiEstaticos.end(); ++itSemiStatics){
		int offSetX = this->getOffset()->first;
		int offSetY = this->getOffset()->second;
		EntidadSemiEstaticaVista* entidad = (*itSemiStatics).second;
		isometricPosition = UtilsController::GetInstance()->getIsometricPosition(entidad);
		this->picassoHelper->renderObject(	entidad->getPathImage(),
											isometricPosition.first + offSetX - entidad->getWidthPixel() / 2 + DefaultSettings::getTileSize(),
											isometricPosition.second + offSetY - entidad->getWidthPixel() / 2 - DefaultSettings::getTileSize() /2,
											entidad->getWidthPixel(),
											entidad->getLengthPixel(),
											entidad->getPositionOfSprite(runCycles));

	}
}

void JuegoVista::updateOffset(int offsetX,int offsetY){
	this->offset.first = offsetX;
	this->offset.second = offsetY;
}

pair<int,int>* JuegoVista::getOffset(){
	return &this->offset;
}

void JuegoVista::addTile(string surface, int x, int y){
	//TODO validar path valido sino poner por default, quizas deberia estar en el server la validacion
	TileVista* newtile = new TileVista(x,y);
	newtile->setPathImage(gameSettings->getEntityConfig(surface)->getPath());
	this->tiles.push_back(newtile);
}

void JuegoVista::addBuilding(int id, string type, int x, int y, string owner){
	EntidadEstaticaVista *newBuilding = new EntidadEstaticaVista(	gameSettings->getEntityConfig(type)->getAncho(),
																	gameSettings->getEntityConfig(type)->getAlto());
	newBuilding->setName(type);
	newBuilding->setPosition(x,y);
	newBuilding->setId(id);
	newBuilding->setOwner(owner);
	string pathImage="";
	if(type=="flag"){
		pathImage = getPathFlagImage(this->coloursOfClients[owner]);
	}else{
		pathImage = gameSettings->getEntityConfig(type)->getPath();
	}
	newBuilding->setPathImage(pathImage);

	this->buildings.insert(make_pair(id,newBuilding));
}

void JuegoVista::addSemiEstaticEntity(int id, string type, int x, int y, string owner){
	EntidadSemiEstaticaVista* newSemiStatic = new EntidadSemiEstaticaVista(	gameSettings->getEntityConfig(type)->getAncho(),
																			gameSettings->getEntityConfig(type)->getAlto(),
																			gameSettings->getEntityConfig(type)->getPixelsDimension(),
																			gameSettings->getEntityConfig(type)->getPixelsDimension(),
																			gameSettings->getEntityConfig(type)->getFps());
	newSemiStatic->setName(type);
	newSemiStatic->setPosition(x,y);
	newSemiStatic->setPathImage(gameSettings->getEntityConfig(type)->getPath());
	newSemiStatic->setDelay(gameSettings->getEntityConfig(type)->getDelay());
	newSemiStatic->setFramesInLineFile(gameSettings->getEntityConfig(type)->getTotalFramesLine());
	newSemiStatic->setId(id);
	newSemiStatic->setOwner(owner);
	this->semiEstaticos.insert(make_pair(id,newSemiStatic));
}

void JuegoVista::addDinamicEntity(int id, string type, int x, int y, int active, string owner,int health,int strength,float precision){
	EntidadDinamicaVista* newPersonaje = new EntidadDinamicaVista(	gameSettings->getEntityConfig(type)->getName(),
																	gameSettings->getEntityConfig(type)->getPixelsDimension(),
																	gameSettings->getEntityConfig(type)->getPixelsDimension(),
																	gameSettings->getEntityConfig(type)->getFps());
	//seteo atributos
	newPersonaje->setName(type);
	newPersonaje->setPosition(x,y);
	newPersonaje->setOwner(owner);
	newPersonaje->setHealth(health);
	newPersonaje->setStrength(health);
	newPersonaje->setPrecision(precision);
	//agrego la posicion inicial de pantalla
	pair<float,float> initialScreenPos = UtilsController::GetInstance()->getIsometricPosition(x,y);
	newPersonaje->setInitialScreenPosition(initialScreenPos.first,initialScreenPos.second);
	newPersonaje->setPathImage(gameSettings->getEntityConfig(type)->getPath());

	newPersonaje->setDelay(gameSettings->getEntityConfig(type)->getDelay());
	newPersonaje->setFramesInLineFile(gameSettings->getEntityConfig(type)->getTotalFramesLine());
	newPersonaje->setId(id);
	this->personajes.insert(make_pair(id,newPersonaje));
}

void JuegoVista::drawMiniMap() {
	this->miniMapVista = new MiniMapVista();
	//dibujo el minimap
	for(list<TileVista*>::iterator itTiles = this->tiles.begin(); itTiles!=this->tiles.end(); ++itTiles){
		this->miniMapVista->makeMiniPos((*itTiles)->getPosX(), (*itTiles)->getPosY());
		this->picassoHelper->renderObject(	this->miniMapVista->getMiniTilePath(),
											this->miniMapVista->getMiniPosX(),
											this->miniMapVista->getMiniPosY(),
											this->miniMapVista->getMiniWidth(),
											this->miniMapVista->getMiniHeight());
		}

	//dibujo las entidades estaticas
	for(map<int,EntidadEstaticaVista*>::iterator itEstaticos = this->buildings.begin(); itEstaticos!=this->buildings.end(); ++itEstaticos){
		pair<int,int>* position;
		EntidadEstaticaVista* entidad = (*itEstaticos).second;
		position = entidad->getPosition();
		int x = position->first;
		int y =  position->second;
		this->miniMapVista->makeMiniPos(x,y);
		colour colourClient = this->coloursOfClients[entidad->getOwner()];
		this->picassoHelper->renderObject(	DefaultSettings::getPathTileColour(convertColourToString(colourClient)),
											this->miniMapVista->getMiniPosX(),
											this->miniMapVista->getMiniPosY(),
											this->miniMapVista->getMiniWidth()+1,
											this->miniMapVista->getMiniHeight()+1);
	}

	//Dibujo los semi estaticos
	for(map<int,EntidadSemiEstaticaVista*>::iterator itSemiStatics = this->semiEstaticos.begin(); itSemiStatics!=this->semiEstaticos.end(); ++itSemiStatics){
		EntidadSemiEstaticaVista* entidad = (*itSemiStatics).second;
		int x = entidad->getPosition()->first;
		int y = entidad->getPosition()->second;
		this->miniMapVista->makeMiniPos(x,y);
		colour colourClient = this->coloursOfClients[entidad->getOwner()];
		this->picassoHelper->renderObject(	DefaultSettings::getPathTileColour(convertColourToString(colourClient)),
											this->miniMapVista->getMiniPosX(),
											this->miniMapVista->getMiniPosY(),
											this->miniMapVista->getMiniWidth()+1,
											this->miniMapVista->getMiniHeight()+1);
	}



	//dibujo los personajes
	for(map<int,EntidadDinamicaVista*>::iterator itDinamicos = this->personajes.begin(); itDinamicos!=this->personajes.end(); ++itDinamicos){
		pair<int,int>* cartesianPosition = (*itDinamicos).second->getPosition();
		this->miniMapVista->makeMiniPos(cartesianPosition->first, cartesianPosition->second);
		colour colourClient = this->coloursOfClients[(*itDinamicos).second->getOwner()];
		this->picassoHelper->renderObject(	DefaultSettings::getPathTileColour(convertColourToString(colourClient)),
											this->miniMapVista->getMiniPosX() ,
											this->miniMapVista->getMiniPosY(),
											this->miniMapVista->getMiniWidth(),
											this->miniMapVista->getMiniHeight());
	}
	for(list<TileVista*>::iterator itTiles = this->tiles.begin(); itTiles!=this->tiles.end(); ++itTiles){
		this->miniMapVista->makeMiniPos((*itTiles)->getPosX(), (*itTiles)->getPosY());
		if ((*itTiles)->getSeen()){
			if ( (*itTiles)->getFogged()) {
				this->picassoHelper->renderFogOfWar(this->gameSettings->getPathOfFoggedTile(),
																this->miniMapVista->getMiniPosX(),
																this->miniMapVista->getMiniPosY(),
																this->miniMapVista->getMiniWidth(),
																this->miniMapVista->getMiniHeight());
			}
		} else {
			this->picassoHelper->renderObject(	this->miniMapVista->getMiniUnseenTilePath(),
																this->miniMapVista->getMiniPosX(),
																this->miniMapVista->getMiniPosY(),
																this->miniMapVista->getMiniWidth(),
																this->miniMapVista->getMiniHeight());
		}
	}
}

map<int,EntidadDinamicaVista*>* JuegoVista::getPersonajes(){
	return &this->personajes;
}

EntidadPartidaVista* JuegoVista::getEntityById(int id){
	map<int, EntidadEstaticaVista*>::iterator itBuildings = this->buildings.find(id);
	if( itBuildings != this->buildings.end()){
		return itBuildings->second;
	}
	map<int, EntidadSemiEstaticaVista*>::iterator itSemiEstaticos = this->semiEstaticos.find(id);
	if( itSemiEstaticos != this->semiEstaticos.end()){
		return itSemiEstaticos->second;
	}
	map<int, EntidadDinamicaVista*>::iterator itPersonajes = this->personajes.find(id);
	if( itPersonajes != this->personajes.end()){
		return itPersonajes->second;
	}
	return NULL;
}

EntidadDinamicaVista* JuegoVista::getDinamicEntityById(int id){
	map<int,EntidadDinamicaVista*>::iterator itPersonajes = this->personajes.find(id);
	if(itPersonajes!=this->personajes.end()){
		return itPersonajes->second;
	}
	return NULL;
}

map<string,string> JuegoVista::getEntityAttributes(EntidadPartidaVista* entidad){
	map<string,string> mapInThisPosition = map<string,string>();
	stringstream ss;
	ss.str("");
	ss << entidad->getId();
	mapInThisPosition.insert(make_pair("id",ss.str()));
	mapInThisPosition.insert(make_pair("name", entidad->getName()));
	mapInThisPosition.insert(make_pair("path", entidad->getPathImage()));
	mapInThisPosition.insert(make_pair("owner", entidad->getOwner()));
	ss.str("");
	ss << entidad->getHealth();
	mapInThisPosition.insert(make_pair("health", ss.str()));
	return mapInThisPosition;
}


void JuegoVista::deleteStaticEntityById(int id){
	map<int,EntidadEstaticaVista*>::iterator itEstaticos = this->buildings.find(id);
	this->buildings.erase(itEstaticos);
}

void JuegoVista::deleteDinamicEntityById(int id){
	map<int, EntidadDinamicaVista*>::iterator itEnemy = this->personajes.find(id);
	if( itEnemy != this->personajes.end()){
		this->personajes.erase(itEnemy);
		return;		
	}
}

void JuegoVista::deleteEntityById(int id){
	map<int, EntidadDinamicaVista*>::iterator itEnemy = this->personajes.find(id);
	if( itEnemy != this->personajes.end() ){
		this->personajes.erase(itEnemy);
		return;		
	}
	map<int,EntidadEstaticaVista*>::iterator itEstaticos = this->buildings.find(id);
	if( itEstaticos != this->buildings.end() ){
		this->buildings.erase(itEstaticos);
		return;
	}
}

map<string,string> JuegoVista::getEntityAt(pair<int,int> position){
	int x = position.first;
	int y = position.second;
	for(map<int,EntidadDinamicaVista*>::iterator itDinamicos = this->personajes.begin(); itDinamicos!=this->personajes.end(); ++itDinamicos){
		pair<int,int>* entityPosition = (*itDinamicos).second->getPosition();
		if(entityPosition->first==x && entityPosition->second==y){
			return this->getEntityAttributes((*itDinamicos).second);
		}
	}
	for(map<int,EntidadEstaticaVista*>::iterator itEstaticos = this->buildings.begin(); itEstaticos!=this->buildings.end(); ++itEstaticos){
		pair<int,int>* entityPosition = (*itEstaticos).second->getPosition();
		int width = (*itEstaticos).second->getWidth();
		int length = (*itEstaticos).second->getLength();
		if(entityPosition->first<=x and (entityPosition->first+width-1)>=x){
			if(entityPosition->second<=y and (entityPosition->second+length-1)>=y){
				return this->getEntityAttributes((*itEstaticos).second);
			}
		}
	}
	for(map<int,EntidadSemiEstaticaVista*>::iterator itSemiDinamicos = this->semiEstaticos.begin(); itSemiDinamicos!=this->semiEstaticos.end(); ++itSemiDinamicos){
		pair<int,int>* entityPosition = (*itSemiDinamicos).second->getPosition();
		if(entityPosition->first==x && entityPosition->second==y){
			return this->getEntityAttributes((*itSemiDinamicos).second);
		}
	}
	return map<string,string>();
}

void JuegoVista::setVisibleTile(int x,int y) {
	for (list<TileVista* >::iterator it = tiles.begin(); it != tiles.end(); ++it) {
		if ( (x == (*it)->getPosX()) && (y == (*it)->getPosY())) {
			(*it)->saw();
		}
	}
}

void JuegoVista::setFoggedTiles(string userName) {
	for(list<TileVista*>::iterator itTiles = this->tiles.begin(); itTiles!=this->tiles.end(); ++itTiles){
		if ((*itTiles)->getSeen()) {
			(*itTiles)->setFogged(true);
		}
	}

	for(map<int,EntidadDinamicaVista*>::iterator itDinamicos = this->personajes.begin(); itDinamicos!=this->personajes.end(); ++itDinamicos){
		EntidadDinamicaVista * entidad = (*itDinamicos).second;
		if(entidad->getOwner()==userName){
			pair<int,int>* position = entidad->getPosition();
				int rangeEntity = this->gameSettings->getRangeVisibility();// TODO aca se deberia usar entidad->getRangeVisibility(), para esto cada entidad deberia saber su rango de visibilidad
				for (int x = position->first - rangeEntity; x <= position->first + rangeEntity; x++) {
					if ( (x>=0) && (x < gameSettings->getMapWidth())) {
						for (int y = position->second-rangeEntity ; y <= position->second+rangeEntity ; y++) {
							if ((y>=0) && (y < this->gameSettings->getMapHeight())) {
								if((x+y >= position->first + position->second - rangeEntity) && (x+y <= position->first + position->second + rangeEntity)
								&& (x-y >= position->first - position->second - rangeEntity) && (x-y <= position->first - position->second + rangeEntity)) {
									for(list<TileVista*>::iterator itTiles = this->tiles.begin(); itTiles!=this->tiles.end(); ++itTiles){
										if ((*itTiles)->getFogged() && (*itTiles)->getPosX() == x && (*itTiles)->getPosY() == y) {
											(*itTiles)->setFogged(false);
										}
									}
								}
							}
						}
					}
				}
		}
	}
}

bool JuegoVista::isEnemyEntityVisible(pair< int, int> pos) {
	for(list<TileVista*>::iterator itTiles = this->tiles.begin(); itTiles!=this->tiles.end(); ++itTiles){
		if ((*itTiles)->getFogged() && (*itTiles)->getPosX() == pos.first && (*itTiles)->getPosY() == pos.second) return false;
	}
	return true;
}

void JuegoVista::drawResources(ResourceCounter* resourceCounter) {
	map<string,int> resources;
	resources["alimento"] = resourceCounter->getAlimento();
	resources["madera"] = resourceCounter->getMadera();
	resources["oro"] = resourceCounter->getOro();
	resources["roca"] = resourceCounter->getRoca();
	this->menuVista->drawResources(resources);
}

void JuegoVista::addResourceToConsume(int idResourse){
	map<int, EntidadEstaticaVista*>::iterator it = this->buildings.find(idResourse);
	if( it != this->buildings.end() ){
		pair<int,int>* position = (*it).second->getPosition();
		this->resoursesToConsume.insert(make_pair(make_pair(position->first,position->second),idResourse));
		return;
	}
}

int JuegoVista::consumeResource(EntidadDinamicaVista* entidad){
	pair<int,int> isometricPosition = UtilsController::GetInstance()->getIsometricPosition(entidad->getPosition()->first, entidad->getPosition()->second);
	map<pair<int,int>, int>::iterator it = this->resoursesToConsume.find(make_pair(entidad->getPosition()->first,entidad->getPosition()->second));
	if( it != this->resoursesToConsume.end()){
		if (isometricPosition.first==entidad->getScreenPosition().first && isometricPosition.second==entidad->getScreenPosition().second){
			int id =(*it).second;
			this->resoursesToConsume.erase(it);
			return id;
		}
	}
	return 0;
}

void JuegoVista::setColour(string owner,int iColour) {
	colour c = static_cast<colour>(iColour);
	this->coloursOfClients[owner] = c;
}

void JuegoVista::deleteEntitiesOfClient(string clientName){
	for(map<int,EntidadDinamicaVista*>::iterator itDinamicos = this->personajes.begin(); itDinamicos!=this->personajes.end(); ++itDinamicos){
		if(itDinamicos->second->getOwner()==clientName){
			this->personajes.erase(itDinamicos);
		}
	}
}

string JuegoVista::getPathFlagImage(colour colorClient){
	return DefaultSettings::getPathFlagImage(this->convertColourToString(colorClient));
}

string JuegoVista::convertColourToString(colour colorClient){
	switch(colorClient){
	case red: return "red";
	case blue: return "blue";
	case yellow: return "yellow";
	case lightGreen: return "lightGreen";
	default: return "";
	}
}

void JuegoVista::setResourceCounter(ResourceCounter* resourceCounter) {
	this->resourceCounter = resourceCounter;
}

ResourceCounter* JuegoVista::getResourceCounter() {
	return this->resourceCounter ;
}

JuegoVista::~JuegoVista() {
//	this->picassoHelper()->~PicassoHelper();
	delete(this->menuVista);
	this->menuVista=NULL;
	delete(this->miniMapVista);
	this->miniMapVista=NULL;
	delete(this->picassoHelper);
	this->picassoHelper=NULL;
	this->gameSettings=NULL;
	this->resourceCounter=NULL;
}
