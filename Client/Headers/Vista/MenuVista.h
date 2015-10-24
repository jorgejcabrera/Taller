/*
 * MenuVista.h
 *
 *  Created on: 5/10/2015
 *      Author: nico
 */

#ifndef SOURCE_MODELO_MENUVISTA_H_
#define SOURCE_MODELO_MENUVISTA_H_

#include <string>
#include "../Modelo/PicassoHelper.h"
#include "../Modelo/GameSettings.h"

namespace std {

class MenuVista {

private:
	string pathImage = "../../Taller/Images/Menu/Menu3.jpg";
	string pathPergamino = "../../Taller/Images/Menu/pergamino.jpg";
	int bigHeight = 120;
	int littleStripSise = 10;
	int mediumStripSise = 20;
	int miniMapWidth ;
	int miniMapHeight = 0;

public:
	MenuVista();
	void drawMe();
	string getPath();
	int getPosX();
	int getPosY();
	int getMiniMapWidht();
	int getMiniMapHeight();
	virtual ~MenuVista();
};

} /* namespace std */

#endif /* SOURCE_MODELO_MENUVISTA_H_ */
