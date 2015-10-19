/*
 * JuegoVista.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "../../Headers/Vista/JuegoVista.h"

JuegoVista::JuegoVista() {
	gameSettings = GameSettings::GetInstance();
}

void JuegoVista::createView(){
	picassoHelper = PicassoHelper::GetInstance(gameSettings->getScreenWidth(), gameSettings->getScreenHeight());
}

void JuegoVista::drawIsometricMap(){
	int posX = 0;
	int posY = 0;
	int offsetX = this->getOffset()->first;
	int offsetY = this->getOffset()->second;
	//TODO: ver como obtener la lista de TILESVISTA
	//TODO: Juego vista no deberia contener la listade tilesVista?

	/*for (map<pair<int,int>,TileVista*>::iterator it = this->juego->getMap()->getTiles()->begin(); it != this->juego->getMap()->getTiles()->end();++it){
		TileVista* tileActual = (*it).second;
		//transformo coordenadas cartesianas a isométricas
		posY = (tileActual->getPosX()+tileActual->getPosY()) * gameSettings->getTileSize() / 2 + offsetY;
		posX = (tileActual->getPosX()-tileActual->getPosY()) * gameSettings->getTileSize() + gameSettings->getScreenWidth() / 2 + offsetX;	//comienzo a dibujar de la mitad de la pantalla
		this->picassoHelper->renderObject(tileActual->getPathImage(),posX,posY,  gameSettings->getTileSize() * 2, gameSettings->getTileSize());
	}*/
}

void JuegoVista::drawStaticEntities(int runCycles){
	pair<int,int> isometricPosition;
	int offSetX = this->getOffset()->first;
	int offSetY = this->getOffset()->second;

	//TODO: Juego vista no deberia contener la listade Entidades??
	/*
	for(map<pair<int,int>,EntidadPartidaVista*>::iterator it=this->juego->getMap()->getEntities()->begin();it!=this->juego->getMap()->getEntities()->end();++it){
		EntidadPartidaVista* entidad = (*it).second;
		isometricPosition = UtilsController::GetInstance()->getIsometricPosition(entidad);
		entidad->drawMe(isometricPosition,offSetX,offSetY,runCycles );
	}*/
}

void JuegoVista::render(int runCycles){
	this->picassoHelper->clearView();
	this->drawIsometricMap();
	this->drawDinamicEntities(runCycles);
	this->drawStaticEntities(runCycles);
	this->picassoHelper->renderView();
}

void JuegoVista::drawDinamicEntities(int runCycles){
	//TODO: Juego vista no deberia contener la lista de soldados?
	/*
	pair<float,float>* screenPosition = juego->getProtagonista()->getScreenPosition();
	int offSetX = this->juego->getOffset()->first;
	int offSetY = this->juego->getOffset()->second;
	this->picassoHelper->renderObject(this->juego->getProtagonista()->getPathImage(), screenPosition->first - gameSettings->getTileSize()/2 + offSetX, screenPosition->second - juego->getProtagonista()->getLengthPixel() / 2 + offSetY, gameSettings->getTileSize(), gameSettings->getTileSize(), this->juego->getProtagonista()->getPositionOfSprite(runCycles));
	*/
}

void JuegoVista::actualizarOffset(int offsetX,int offsetY){
	this->offset.first = offsetX;
	this->offset.second = offsetY;
}

pair<int,int>* JuegoVista::getOffset(){
	return &this->offset;
}

JuegoVista::~JuegoVista() {
//	this->picassoHelper()->~PicassoHelper();
	delete(this->picassoHelper);
	this->picassoHelper=NULL;
	this->gameSettings=NULL;
}

void JuegoVista::addTile(string surface, int x, int y){
	//TODO validar path valido sino poner por default, quizas deberia estar en el server la validacion
	//TODO falta agregar el offset para dibujar
	//TODO lo guardo en posiciones cartecianas, despues lo voy a convertir cuando lo tenga que dibujar
	//int posY =(x+y) * gameSettings->getTileSize() / 2;
	//int posX =(x-y) * gameSettings->getTileSize() + gameSettings->getScreenWidth() / 2;
	TileVista *newtile = new TileVista(x,y);
	newtile->setPathImage(gameSettings->getEntityConfig(surface)->getPath());
	this->tiles.push_back(newtile);
}

void JuegoVista::addBuilding(int id, string type, int x, int y){
	EntidadEstaticaVista *newBuilding = new EntidadEstaticaVista(x,y);
	newBuilding->setPathImage(gameSettings->getEntityConfig(type)->getPath());
	newBuilding->setId(id);
	this->buildings.insert(make_pair(id,newBuilding));
	//cout << "EDIFICIO: "<< id << " nombre " << type << " x " << x << " y " << y << " path " << newBuilding->getPathImage()<< endl;
}
