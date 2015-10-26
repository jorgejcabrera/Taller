/*
 * MiniMap.h
 *
 *  Created on: 8/10/2015
 *      Author: nico
 */

#ifndef MINIMAPVISTA_H_
#define MINIMAPVISTA_H_

#include "../../Headers/Modelo/GameSettings.h"

namespace std {

class MiniMapVista {
private:
	GameSettings* gameSettings;
	int miniTilePosX;
	int miniTilePosY;
	string miniTilePath;
	string miniUnseenTilePath;
	string miniFoggedTilePath;
	int alturaMenu;
	int diagonal;
	int offsetY ;
	int offsetX ;
	int miniTileSize;
	int miniTileHeight;
	int miniTileWidth;
	int miniEntityPosX;
	int miniEntityPosY;
	string miniEntityPath;
	int miniEntitySize;
	int miniCharacterPosX;
	int miniCharacterPosY;
	string miniCharacterPath;
	int miniCharacterSize;
public:
	MiniMapVista();
	virtual ~MiniMapVista();
	void makeMiniTilePos(int posX, int posY);
	string getMiniTilePath();
	string getMiniUnseenTilePath();
	string getMiniFoggedTilePath();
	int getTilePosX();
	int getTilePosY();
	int getMiniTileSize();
	void makeMiniEntityPos(int posX, int posY);
	string getEntityPath();
	int getEntityPosX();
	int getEntityPosY();
	int getMiniEntitySize();
	void makeMiniCharacterPos(int posX, int posY);
	string getCharacterPath();
	int getCharacterPosX();
	int getCharacterPosY();
	int getMiniCharacterSize();
};

} /* namespace std */

#endif /* MINIMAP_H_ */
