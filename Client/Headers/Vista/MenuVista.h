/*
 * MenuVista.h
 *
 *  Created on: 5/10/2015
 *      Author: nico
 */

#ifndef SOURCE_MODELO_MENUVISTA_H_
#define SOURCE_MODELO_MENUVISTA_H_

#include <string>
#include <sstream>
#include "../Modelo/PicassoHelper.h"
#include "../Modelo/GameSettings.h"

namespace std {

class MenuVista {

private:
	string pathImage;
	string pathPergamino;
	int bigHeight;
	int littleStripSise;
	int mediumStripSise;
	int miniMapWidth;
	int miniMapHeight;
	bool drawDescription;
	map<string,string> strings;
	bool drawEntities;
	map<string,int> selectedEntities;
	int posXvertexFirstButton;
	int posYvertexFirstButton;
	int sideFirstButton;

public:
	MenuVista();
	void drawMe();
	string getPath();
	int getPosX();
	int getPosY();
	int getMiniMapWidht();
	int getMiniMapHeight();
	void drawEntityDescription();
	void deselectedEntity();
	void setSelectedEntityDescription(map<string,string> description);
	void drawResources(map<string,int> resources);
	pair<int, string> getTypeOfNewEntity(int posMouseX,int posMouseY);
	void drawEntitiesSelected();
	void setSelectedEntities(map<string,int>);
	virtual ~MenuVista();
};

} /* namespace std */

#endif /* SOURCE_MODELO_MENUVISTA_H_ */
