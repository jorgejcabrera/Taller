/*
 * MiniMapVista.cpp
 *
 *  Created on: 8/10/2015
 *      Author: nico
 */

#include "../../Headers/Vista/MiniMapVista.h"

namespace std {

MiniMapVista::MiniMapVista() {
	gameSettings = GameSettings::GetInstance();
	miniTilePosX = 0;
	miniTilePosY = 0;
	miniCharacterPosX = 0;
	miniCharacterPosY = 0;
	miniEntityPosX = 0;
	miniEntityPosY = 0;

	miniTilePath = "../../Taller/Images/Tiles/tileVerde.png";
	miniUnseenTilePath = "../../Taller/Images/Tiles/tileNegro.png";
	miniFoggedTilePath = "../../Taller/Images/Tiles/tilefog.png";
	miniCharacterPath = "../../Taller/Images/Tiles/tileAzul.png";
	miniEntityPath = "../../Taller/Images/Tiles/tileAzul.png";

	alturaMenu = gameSettings->getAlturaMenuInferior();
	diagonal = sqrt(pow(gameSettings->getMapHeight(),2) + pow(gameSettings->getMapWidth(),2));
	offsetY = gameSettings->getScreenHeight() - alturaMenu;
	offsetX = gameSettings->getScreenWidth()/8 * 7; // 7/8 del mapa
	miniTileSize =7;
	miniCharacterSize =5;
	miniEntitySize =7;
	miniTileHeight = alturaMenu/(diagonal);
	miniTileWidth = (gameSettings->getScreenWidth()*2/4) / diagonal;
}

void MiniMapVista::makeMiniTilePos(int posX, int posY) {
	this->miniTilePosY = (posX+posY)*miniTileHeight + offsetY;
	this->miniTilePosX = (posX-posY)*miniTileWidth/3+ offsetX;
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

int MiniMapVista::getTilePosX() {
	return this->miniTilePosX;
}

int MiniMapVista::getTilePosY() {
	return this->miniTilePosY;
}

int MiniMapVista::getMiniTileSize() {
	return this->miniTileSize;
}

string MiniMapVista::getEntityPath() {
	return this->miniEntityPath;
}

int MiniMapVista::getEntityPosX() {
	return this->miniEntityPosX;
}

int MiniMapVista::getEntityPosY() {
	return this->miniEntityPosY;
}

int MiniMapVista::getMiniEntitySize() {
	return this->miniEntitySize;
}

void MiniMapVista::makeMiniEntityPos(int posX, int posY) {
	this->miniEntityPosY = (posX+posY)*miniTileHeight + offsetY;
	this->miniEntityPosX = (posX-posY)*miniTileWidth/3+ offsetX;
}

string MiniMapVista::getCharacterPath() {
	return this->miniCharacterPath;
}

int MiniMapVista::getCharacterPosX() {
	return this->miniCharacterPosX;
}

int MiniMapVista::getCharacterPosY() {
	return this->miniCharacterPosY;
}

int MiniMapVista::getMiniCharacterSize() {
	return this->miniCharacterSize;
}

void MiniMapVista::makeMiniCharacterPos(int posX, int posY) {
	this->miniCharacterPosY = (posY*2 /gameSettings->getTileSize()) *miniTileHeight + offsetY;
	this->miniCharacterPosX = (((posX)- (gameSettings->getScreenWidth() / 2))/ gameSettings->getTileSize() )*miniTileWidth/3+ offsetX;
}

MiniMapVista::~MiniMapVista() {
	this->gameSettings = NULL;
}

} /* namespace std */
