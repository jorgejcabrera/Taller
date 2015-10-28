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
}

void JuegoVista::createView(){
	picassoHelper = PicassoHelper::GetInstance(gameSettings->getScreenWidth(), gameSettings->getScreenHeight());
}

void JuegoVista::render(int runCycles){
	this->picassoHelper->clearView();
	this->drawIsometricMap();
	this->setFoggedTiles();
	this->drawDinamicEntities(runCycles);
	this->drawStaticEntities(runCycles);
	this->drawSemiStaticsEntities(runCycles);
	this->drawFog();
	this->drawMenu();
	this->drawMiniMap();
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

	//personajes que no son del cliente
	for(map<int,EntidadDinamicaVista*>::iterator itDinamicos = this->personajes.begin(); itDinamicos!=this->personajes.end(); ++itDinamicos){
		entidad = (*itDinamicos).second;
		drawDinamicEntity(entidad,runCycles);
		}

	//personajes que son del cliente
	for(map<int,EntidadDinamicaVista*>::iterator itDinamicos = this->misPersonajes.begin(); itDinamicos!=this->misPersonajes.end(); ++itDinamicos){
		entidad = (*itDinamicos).second;
		drawDinamicEntity(entidad,runCycles);
	}
}

void JuegoVista::drawDinamicEntity(EntidadDinamicaVista* entidad, int runCycles){
		int offSetX = this->getOffset()->first;
		int offSetY = this->getOffset()->second;
		pair<int,int> screenPosition = entidad->getScreenPosition();
		entidad->trasladarse();
		this->picassoHelper->renderObject(	entidad->getPathImage(),
											screenPosition.first - entidad->getWidthPixel()/2 + offSetX,
											screenPosition.second  - entidad->getLengthPixel()/2 + offSetY,
											gameSettings->getTileSize(),
											gameSettings->getTileSize(),
											entidad->getPositionOfSprite(runCycles));
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

void JuegoVista::actualizarOffset(int offsetX,int offsetY){
	this->offset.first = offsetX;
	this->offset.second = offsetY;
}

pair<int,int>* JuegoVista::getOffset(){
	return &this->offset;
}

void JuegoVista::addTile(string surface, int x, int y){
	//TODO validar path valido sino poner por default, quizas deberia estar en el server la validacion
	//TODO falta agregar el offset para dibujar
	TileVista* newtile = new TileVista(x,y);
	newtile->setPathImage(gameSettings->getEntityConfig(surface)->getPath());
	this->tiles.push_back(newtile);
}

void JuegoVista::addBuilding(int id, string type, int x, int y){
	EntidadEstaticaVista *newBuilding = new EntidadEstaticaVista(gameSettings->getEntityConfig(type)->getAncho(),gameSettings->getEntityConfig(type)->getAlto());
	newBuilding->setName(type);
	newBuilding->setPosition(x,y);
	newBuilding->setPathImage(gameSettings->getEntityConfig(type)->getPath());
	newBuilding->setId(id);
	this->buildings.insert(make_pair(id,newBuilding));
}

void JuegoVista::addSemiEstaticEntity(int id, string type, int x, int y){
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
	this->semiEstaticos.insert(make_pair(id,newSemiStatic));
}

void JuegoVista::addDinamicEntity(int id, string type, int x, int y, bool imTheOwner, int active){
	EntidadDinamicaVista* newPersonaje = new EntidadDinamicaVista(	gameSettings->getEntityConfig(type)->getName(),
																	gameSettings->getEntityConfig(type)->getPixelsDimension(),
																	gameSettings->getEntityConfig(type)->getPixelsDimension(),
																	gameSettings->getEntityConfig(type)->getFps());
	//seteo atributos
	newPersonaje->setName(type);
	newPersonaje->setPosition(x,y);
	//agrego la posicion inicial de pantalla
	pair<float,float> initialScreenPos = UtilsController::GetInstance()->getIsometricPosition(x,y);
	newPersonaje->setInitialScreenPosition(initialScreenPos.first,initialScreenPos.second);
	newPersonaje->setPathImage(gameSettings->getEntityConfig(type)->getPath());

	if((active<0) && (!imTheOwner)){
		newPersonaje->setPathImage(gameSettings->getEntityConfig("soldadoDesconectado")->getPath());
	}

	newPersonaje->setDelay(gameSettings->getEntityConfig(type)->getDelay());
	newPersonaje->setFramesInLineFile(gameSettings->getEntityConfig(type)->getTotalFramesLine());
	newPersonaje->setId(id);

	if(imTheOwner){
		this->misPersonajes.insert(make_pair(id,newPersonaje));
	}else{
		this->personajes.insert(make_pair(id,newPersonaje));
	}
}

void JuegoVista::drawMiniMap() {
	this->miniMapVista = new MiniMapVista();
	//dibujo el minimap
	for(list<TileVista*>::iterator itTiles = this->tiles.begin(); itTiles!=this->tiles.end(); ++itTiles){
		this->miniMapVista->makeMiniTilePos((*itTiles)->getPosX(), (*itTiles)->getPosY());
		this->picassoHelper->renderObject(	this->miniMapVista->getMiniTilePath(),
											this->miniMapVista->getTilePosX(),
											this->miniMapVista->getTilePosY(),
											this->miniMapVista->getMiniTileSize(),
											this->miniMapVista->getMiniTileSize());
		}

	//dibujo las entidades estaticas
	for(map<int,EntidadEstaticaVista*>::iterator itEstaticos = this->buildings.begin(); itEstaticos!=this->buildings.end(); ++itEstaticos){
		pair<int,int>* position;
		EntidadEstaticaVista* entidad = (*itEstaticos).second;
		position = entidad->getPosition();
		int x = position->first;
		int y =  position->second;
		this->miniMapVista->makeMiniEntityPos(x,y);
		this->picassoHelper->renderObject(	this->miniMapVista->getEntityPath(),
											this->miniMapVista->getEntityPosX(),
											this->miniMapVista->getEntityPosY(),
											this->miniMapVista->getMiniEntitySize(),
											this->miniMapVista->getMiniEntitySize());
	}

	//dibujo las entidades dinamicas
	pair<int,int> isometricPosition;
	EntidadDinamicaVista* entidad;

	//deberia dibujar los personajes que son del cliente
	for(map<int,EntidadDinamicaVista*>::iterator itDinamicos = this->personajes.begin(); itDinamicos!=this->personajes.end(); ++itDinamicos){
		pair<int,int>* cartesianPosition = (*itDinamicos).second->getPosition();
		pair<int,int> screenPosition = UtilsController::GetInstance()->getIsometricPosition(cartesianPosition->first,cartesianPosition->second);
		this->miniMapVista->makeMiniCharacterPos(screenPosition.first, screenPosition.second);
		this->picassoHelper->renderObject(this->miniMapVista->getCharacterPath(),this->miniMapVista->getCharacterPosX() , this->miniMapVista->getCharacterPosY(), this->miniMapVista->getMiniCharacterSize(), this->miniMapVista->getMiniCharacterSize());
	}
	//dibujo los personajes que son del cliente
	for(map<int,EntidadDinamicaVista*>::iterator itDinamicos = this->misPersonajes.begin(); itDinamicos!=this->misPersonajes.end(); ++itDinamicos){
		pair<int,int>* cartesianPosition = (*itDinamicos).second->getPosition();
		pair<int,int> screenPosition = UtilsController::GetInstance()->getIsometricPosition(cartesianPosition->first,cartesianPosition->second);
		this->miniMapVista->makeMiniCharacterPos(screenPosition.first, screenPosition.second);
		this->picassoHelper->renderObject(this->miniMapVista->getCharacterPath(),this->miniMapVista->getCharacterPosX() , this->miniMapVista->getCharacterPosY(), this->miniMapVista->getMiniCharacterSize(), this->miniMapVista->getMiniCharacterSize());
	}


	for(list<TileVista*>::iterator itTiles = this->tiles.begin(); itTiles!=this->tiles.end(); ++itTiles){
		this->miniMapVista->makeMiniTilePos((*itTiles)->getPosX(), (*itTiles)->getPosY());
		if ((*itTiles)->getSeen()){
			if ( (*itTiles)->getFogged()) {
				this->picassoHelper->renderFogOfWar(this->gameSettings->getPathOfFoggedTile(),
																this->miniMapVista->getTilePosX(),
																this->miniMapVista->getTilePosY(),
																this->miniMapVista->getMiniTileSize(),
																this->miniMapVista->getMiniTileSize()/2);
			}
		} else {
			this->picassoHelper->renderObject(	this->miniMapVista->getMiniUnseenTilePath(),
																this->miniMapVista->getTilePosX(),
																this->miniMapVista->getTilePosY(),
																this->miniMapVista->getMiniTileSize(),
																this->miniMapVista->getMiniTileSize());
		}
	}

/*			list<pair<int,int> > unseenTiles;
 * 			for(list<pair<int,int> >::iterator it = unseenTiles.begin(); it!=unseenTiles.end(); ++it){
			this->miniMapVista->makeMiniTilePos((*it).first, (*it).second);
		}
				unseenTiles.push_front(make_pair((*itTiles)->getPosX(),(*itTiles)->getPosY()));

*/
}


map<int,EntidadDinamicaVista*>* JuegoVista::getMyEntities(){
	return &this->misPersonajes;
}

map<int,EntidadDinamicaVista*>* JuegoVista::getPersonajes(){
	return &this->personajes;
}

EntidadDinamicaVista* JuegoVista::getEntityById(int id){
	map<int,EntidadDinamicaVista*>::iterator itPersonajes = this->personajes.find(id);
	if(itPersonajes!=this->personajes.end()){
		return itPersonajes->second;
	}
	map<int,EntidadDinamicaVista*>::iterator itMisPersonajes = this->misPersonajes.find(id);
	if(itMisPersonajes!=this->misPersonajes.end()){
		return itMisPersonajes->second;
	}
}

map<string,string> JuegoVista::buildMapWithEntityData(EntidadPartidaVista* entidad){
	map<string,string> mapInThisPosition = map<string,string>();
	stringstream ss;
	ss.str("");
	ss<<entidad->getId();
	mapInThisPosition.insert(make_pair("id",ss.str()));
	mapInThisPosition.insert(make_pair("name", entidad->getName()));
	mapInThisPosition.insert(make_pair("path", entidad->getPathImage()));
	ss.str("");
	ss<<entidad->getSalud();
	mapInThisPosition.insert(make_pair("salud", ss.str()));
	return mapInThisPosition;
}


void JuegoVista::deleteStaticEntityById(int id){
	map<int,EntidadEstaticaVista*>::iterator itEstaticos = this->buildings.find(id);
	this->buildings.erase(itEstaticos);
}

map<string,string> JuegoVista::entityInThisPosition(int x, int y){
	for(map<int,EntidadDinamicaVista*>::iterator itDinamicos = this->personajes.begin(); itDinamicos!=this->personajes.end(); ++itDinamicos){
		pair<int,int>* entityPosition = (*itDinamicos).second->getPosition();
		if(entityPosition->first==x && entityPosition->second==y){
			return this->buildMapWithEntityData((*itDinamicos).second);
		}
	}
	for(map<int,EntidadDinamicaVista*>::iterator itDinamicos = this->misPersonajes.begin(); itDinamicos!=this->misPersonajes.end(); ++itDinamicos){
		pair<int,int>* entityPosition = (*itDinamicos).second->getPosition();
		if(entityPosition->first==x && entityPosition->second==y){
			return this->buildMapWithEntityData((*itDinamicos).second);
		}
	}

	for(map<int,EntidadEstaticaVista*>::iterator itEstaticos = this->buildings.begin(); itEstaticos!=this->buildings.end(); ++itEstaticos){
		pair<int,int>* entityPosition = (*itEstaticos).second->getPosition();
		int width = (*itEstaticos).second->getWidth();
		int length = (*itEstaticos).second->getLength();
		if(entityPosition->first<=x and (entityPosition->first+width-1)>=x){
			if(entityPosition->second<=y and (entityPosition->second+length-1)>=y){
				return this->buildMapWithEntityData((*itEstaticos).second);
			}
		}
	}

	for(map<int,EntidadSemiEstaticaVista*>::iterator itSemiDinamicos = this->semiEstaticos.begin(); itSemiDinamicos!=this->semiEstaticos.end(); ++itSemiDinamicos){
		pair<int,int>* entityPosition = (*itSemiDinamicos).second->getPosition();
		if(entityPosition->first==x && entityPosition->second==y){
			return this->buildMapWithEntityData((*itSemiDinamicos).second);
		}
	}
	map<string,string> mapEmpty = map<string,string>();
	return mapEmpty;
}

void JuegoVista::setVisibleTile(int x,int y) {
	for (list<TileVista* >::iterator it = tiles.begin(); it != tiles.end(); ++it) {
		if ( (x == (*it)->getPosX()) && (y == (*it)->getPosY())) {
			(*it)->saw();
		}
	}
}

void JuegoVista::actualizarProtagonista(){
	
}

void JuegoVista::setFoggedTiles() {
	for(list<TileVista*>::iterator itTiles = this->tiles.begin(); itTiles!=this->tiles.end(); ++itTiles){
		if ((*itTiles)->getSeen()) {
			(*itTiles)->setFogged(true);
		}
	}

	for(map<int,EntidadDinamicaVista*>::iterator itDinamicos = this->misPersonajes.begin(); itDinamicos!=this->misPersonajes.end(); ++itDinamicos){
		EntidadDinamicaVista * entidad = (*itDinamicos).second;
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

bool JuegoVista::isEnemyEntityVisible(pair< int, int> pos) {
	for(list<TileVista*>::iterator itTiles = this->tiles.begin(); itTiles!=this->tiles.end(); ++itTiles){
		if ((*itTiles)->getFogged() && (*itTiles)->getPosX() == pos.first && (*itTiles)->getPosY() == pos.second) return false;
	}
	return true;
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
}
