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
#include "EntidadPartidaVista.h"

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
	map<string,string> strings;
	map<string,int> selectedEntities;
	EntidadPartidaVista* entitySelected;
	int posXvertexFirstButton;
	int posYvertexFirstButton;
	int sideFirstButton;
	int letterHeight;

public:
	MenuVista();
	void drawMe();
	int getPosX();
	int getPosY();
	int getMiniMapWidht();
	int getMiniMapHeight();
	void drawEntityDescription();
	void deselectedEntity();
	void drawResources(map<string,int> resources);
	pair<int, string> getTypeOfNewEntity(int posMouseX,int posMouseY);
	void drawEntitiesSelected();
	void setSelectedEntities(map<string,int>);
	/*
	* seteo la entidad que voy a mostrar en el menu como seleccionada
	* */
	void setSelectedEntity(EntidadPartidaVista* entity);
	/*
	* armo un string con field y value y llamo a renderEntityText
	* */
	void renderEntityField(string field, string value, int offset);
	/*
	* armo un string con field y value y llamo a renderEntityText
	* */
	void renderEntityField(string field, int value, int offset);
	/*
	 * renderiza el texto recibido
	 */
	void renderEntityText(string text, int offset);
	/*
	* Renderiza la imagen del personaje seleccioando
	* */
	void renderEntityImage(string path);
	virtual ~MenuVista();
};

} /* namespace std */

#endif /* SOURCE_MODELO_MENUVISTA_H_ */
