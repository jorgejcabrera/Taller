/*
 * MiniMapVista.cpp
 *
 *  Created on: 8/10/2015
 *      Author: nico
 */

#include "../../Headers/Vista/MiniMapVista.h"

namespace std {

MiniMapVista::MiniMapVista() {
	GameSettings* gameSettings = GameSettings::GetInstance();
	miniTilePath = "../../Taller/Images/Tiles/tileVerde.png";
	miniUnseenTilePath = "../../Taller/Images/Tiles/tileNegro.png";
	miniFoggedTilePath = "../../Taller/Images/Tiles/tilefog.png";
	miniCharacterPath = "../../Taller/Images/Tiles/blueTile.png";
	miniEnemyCharacterPath = "../../Taller/Images/Tiles/tileRojo.png";
	miniEntityPath = "../../Taller/Images/Tiles/blueTile.png";

	alturaMenu = gameSettings->getAlturaMenuInferior();
	diagonal = sqrt(pow(gameSettings->getMapHeight(),2) + pow(gameSettings->getMapWidth(),2));
	offsetY = gameSettings->getScreenHeight() - alturaMenu;
	offsetX = gameSettings->getScreenWidth()/8 * 7; // 7/8 del mapa
	miniEntitySize =7;
	miniHeight = alturaMenu/gameSettings->getMapHeight();
	miniWidth = (gameSettings->getScreenWidth()/4) / gameSettings->getMapWidth();
	miniPosX = 0;
	miniPosY = 0;
}

void MiniMapVista::makeMiniPos(pair<int,int> position) {
	this->miniPosY = (position.first+position.second)*miniHeight/2 + offsetY;
	this->miniPosX = (position.first-position.second)*miniWidth/2 + offsetX;
}

string MiniMapVista::getMiniTilePath() {
	return this->miniTilePath;
}

string MiniMapVista::getMiniUnseenTilePath() {
	return this->miniUnseenTilePath;
}

string MiniMapVista::getMiniFoggedTilePath() {
	return this->miniFoggedTilePath;
}

string MiniMapVista::getEntityPath() {
	return this->miniEntityPath;
}

string MiniMapVista::getCharacterPath() {
	return this->miniCharacterPath;
}

string MiniMapVista::getEnemyCharacterPath() {
	return this->miniEnemyCharacterPath;
}

int MiniMapVista::getMiniPosX() {
	return this->miniPosX;
}

int MiniMapVista::getMiniPosY() {
	return this->miniPosY;
}

int MiniMapVista::getMiniWidth() {
	return this->miniWidth;
}

int MiniMapVista::getMiniHeight() {
	return this->miniHeight;
}

void MiniMapVista::renderEntity(string pathImage, EntidadPartidaVista* entity){
	this->makeMiniPos(entity->getPosition());
	int miniWidth = this->getMiniWidth() + entity->getWidth()-1;
	int miniHeight = this->getMiniHeight() + entity->getLength()-1;
	PicassoHelper::GetInstance()->renderObject(	pathImage,
												this->getMiniPosX(),
												this->getMiniPosY(),
												miniWidth,
												miniHeight);

}

void MiniMapVista::renderTile(string pathImage, pair<int,int> position){
	this->makeMiniPos(position);
	PicassoHelper::GetInstance()->renderObject(	pathImage,
												this->getMiniPosX(),
												this->getMiniPosY(),
												this->getMiniWidth(),
												this->getMiniHeight());
}

MiniMapVista::~MiniMapVista() {
}
} /* namespace std */
