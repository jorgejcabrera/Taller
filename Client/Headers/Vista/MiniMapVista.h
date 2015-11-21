/*
 * MiniMap.h
 *
 *  Created on: 8/10/2015
 *      Author: nico
 */

#ifndef MINIMAPVISTA_H_
#define MINIMAPVISTA_H_

#include "../../Headers/Modelo/GameSettings.h"
#include "EntidadPartidaVista.h"
#include "../../Headers/Modelo/PicassoHelper.h"

enum colour { red=1, blue, yellow, lightGreen,} ;

namespace std {

class MiniMapVista {
private:
	string miniTilePath;
	string miniUnseenTilePath;
	string miniFoggedTilePath;
	int alturaMenu;
	int diagonal;
	int offsetY ;
	int offsetX ;
	string miniEntityPath;
	int miniEntitySize;
	string miniCharacterPath;
	string miniEnemyCharacterPath;
	int miniPosX;
	int miniPosY;
	int miniWidth;
	int miniHeight;
public:
	MiniMapVista();
	virtual ~MiniMapVista();
	string getMiniTilePath();
	string getMiniUnseenTilePath();
	string getMiniFoggedTilePath();
	string getEntityPath();
	string getCharacterPath();
	string getEnemyCharacterPath();
	void makeMiniPos(pair<int,int> position);
	int getMiniPosX();
	int getMiniPosY();
	int getMiniWidth();
	int getMiniHeight();
	/*
	 * renderiza la entidad en el minimapa
	 */
	void renderEntity(string pathImage, EntidadPartidaVista* entity);
	/*
	 * renderiza los tiles
	 */
	void renderTile(string pathImage, pair<int,int> position);
};

} /* namespace std */

#endif /* MINIMAP_H_ */
