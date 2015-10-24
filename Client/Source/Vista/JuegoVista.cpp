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
	this->drawDinamicEntities(runCycles);
	this->drawStaticEntities(runCycles);
	this->drawSemiStaticsEntities(runCycles);
	this->drawMenu();
	this->drawMiniMap();
	this->picassoHelper->renderView();
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
		posY = ((*itTiles)->getPosX()+(*itTiles)->getPosY()) * gameSettings->getTileSize() / 2 + offsetY;
		posX = ((*itTiles)->getPosX()-(*itTiles)->getPosY()) * gameSettings->getTileSize() + gameSettings->getScreenWidth() / 2 + offsetX;	//comienzo a dibujar de la mitad de la pantalla
		this->picassoHelper->renderObject((*itTiles)->getPathImage(),posX,posY, gameSettings->getTileSize() * 2, gameSettings->getTileSize());
	}
}

void JuegoVista::drawStaticEntities(int runCycles){
	pair<int,int> isometricPosition;
	int offSetX = this->getOffset()->first;
	int offSetY = this->getOffset()->second;

	for(map<int,EntidadEstaticaVista*>::iterator itEstaticos = this->buildings.begin(); itEstaticos!=this->buildings.end(); ++itEstaticos){
		EntidadEstaticaVista* entidad = (*itEstaticos).second;
		isometricPosition = UtilsController::GetInstance()->getIsometricPosition(entidad);
		entidad->drawMe(isometricPosition,offSetX,offSetY,runCycles);
	}
}

void JuegoVista::drawDinamicEntities(int runCycles){
	pair<int,int> isometricPosition;
	EntidadDinamicaVista* entidad;

	//deberia dibujar los personajes que son del cliente
	for(map<int,EntidadDinamicaVista*>::iterator itDinamicos = this->personajes.begin(); itDinamicos!=this->personajes.end(); ++itDinamicos){
		pair<float,float>* screenPosition = (*itDinamicos).second->getScreenPosition();
		entidad = (*itDinamicos).second;
		int offSetX = this->getOffset()->first;
		int offSetY = this->getOffset()->second;
		this->picassoHelper->renderObject(	entidad->getPathImage(),
											screenPosition->first - entidad->getWidthPixel()/2 + offSetX,
											screenPosition->second  - entidad->getLengthPixel()/2 + offSetY,
											gameSettings->getTileSize(),
											gameSettings->getTileSize(),
											entidad->getPositionOfSprite(runCycles));
	}

	//dibujo los personajes que son del cliente
	for(map<int,EntidadDinamicaVista*>::iterator itDinamicos = this->misPersonajes.begin(); itDinamicos!=this->misPersonajes.end(); ++itDinamicos){
		pair<float,float>* screenPosition = (*itDinamicos).second->getScreenPosition();
		entidad = (*itDinamicos).second;
		int offSetX = this->getOffset()->first;
		int offSetY = this->getOffset()->second;
		this->picassoHelper->renderObject(	entidad->getPathImage(),
											screenPosition->first - entidad->getWidthPixel()/2 + offSetX,
											screenPosition->second  - entidad->getLengthPixel()/2 + offSetY,
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
	newPersonaje->setPosition(x,y);
	newPersonaje->setPathImage(gameSettings->getEntityConfig(type)->getPath());
	if(active<0){
		newPersonaje->setPathImage(gameSettings->getEntityConfig("soldadoDesconectado")->getPath());
	}

	newPersonaje->setDelay(gameSettings->getEntityConfig(type)->getDelay());
	newPersonaje->setFramesInLineFile(gameSettings->getEntityConfig(type)->getTotalFramesLine());
	newPersonaje->setId(id);

	pair<int,int> isometricPosition = UtilsController::GetInstance()->getIsometricPosition(newPersonaje);			//paso la posicion cartesiana a isometrica
	newPersonaje->setPathImage(gameSettings->getEntityConfig(type)->getPath());
	isometricPosition.first = isometricPosition.first + gameSettings->getTileSize() + this->getOffset()->first;		//la primera vez que creamos la entidad tenemos que centrarla
	isometricPosition.second = isometricPosition.second + newPersonaje->getLengthPixel()/2 + this->offset.second;
	newPersonaje->setScreenPosition(isometricPosition);

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
		this->picassoHelper->renderObject(this->miniMapVista->getTilePath(),this->miniMapVista->getTilePosX(),this->miniMapVista->getTilePosY(),this->miniMapVista->getMiniTileSize(),this->miniMapVista->getMiniTileSize());
		}

	//dibujo las entidades estaticas
	for(map<int,EntidadEstaticaVista*>::iterator itEstaticos = this->buildings.begin(); itEstaticos!=this->buildings.end(); ++itEstaticos){
		pair<int,int>* position;
		EntidadEstaticaVista* entidad = (*itEstaticos).second;
		position = entidad->getPosition();
		int x = position->first;
		int y =  position->second;
		this->miniMapVista->makeMiniEntityPos(x,y);
		this->picassoHelper->renderObject(this->miniMapVista->getEntityPath(),this->miniMapVista->getEntityPosX(),this->miniMapVista->getEntityPosY(),this->miniMapVista->getMiniEntitySize(),this->miniMapVista->getMiniEntitySize());
	}

	//dibujo las entidades dinamicas
	pair<int,int> isometricPosition;
	EntidadDinamicaVista* entidad;

	//deberia dibujar los personajes que son del cliente
	for(map<int,EntidadDinamicaVista*>::iterator itDinamicos = this->personajes.begin(); itDinamicos!=this->personajes.end(); ++itDinamicos){
		pair<float,float>* screenPosition = (*itDinamicos).second->getScreenPosition();
		this->miniMapVista->makeMiniCharacterPos(screenPosition->first, screenPosition->second);
		this->picassoHelper->renderObject(this->miniMapVista->getCharacterPath(),this->miniMapVista->getCharacterPosX() , this->miniMapVista->getCharacterPosY(), this->miniMapVista->getMiniCharacterSize(), this->miniMapVista->getMiniCharacterSize());
	}
	//dibujo los personajes que son del cliente
	for(map<int,EntidadDinamicaVista*>::iterator itDinamicos = this->misPersonajes.begin(); itDinamicos!=this->misPersonajes.end(); ++itDinamicos){
		pair<float,float>* screenPosition = (*itDinamicos).second->getScreenPosition();
		this->miniMapVista->makeMiniCharacterPos(screenPosition->first, screenPosition->second);
		this->picassoHelper->renderObject(this->miniMapVista->getCharacterPath(),this->miniMapVista->getCharacterPosX() , this->miniMapVista->getCharacterPosY(), this->miniMapVista->getMiniCharacterSize(), this->miniMapVista->getMiniCharacterSize());
	}
}

map<int,EntidadDinamicaVista*>* JuegoVista::getMyEntities(){
	return &this->misPersonajes;
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


JuegoVista::~JuegoVista() {
//	this->picassoHelper()->~PicassoHelper();
	delete(this->picassoHelper);
	this->picassoHelper=NULL;
	this->gameSettings=NULL;
}
