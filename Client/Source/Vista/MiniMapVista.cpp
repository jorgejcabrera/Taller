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

void MiniMapVista::makeMiniPos(int posX, int posY) {
	this->miniPosY = (posX+posY)*miniHeight/2 + offsetY;
	this->miniPosX = (posX-posY)*miniWidth/2 + offsetX;
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

MiniMapVista::~MiniMapVista() {
	this->gameSettings = NULL;
}

string MiniMapVista::getPathOfColour(colour colour) {
	switch (colour) {
	case red : 			return "../../Taller/Images/Tiles/redTile.png";
						break;
	case blue : 		return "../../Taller/Images/Tiles/blueTile.png";
						break;
	case yellow :		return "../../Taller/Images/Tiles/yellowTile.png";
						break;
	case lightGreen : 	return "../../Taller/Images/Tiles/lightGreenTile.png";
						break;
	default : 			return "";
	}
}

} /* namespace std */
