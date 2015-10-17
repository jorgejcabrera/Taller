/*
 * EntidadPartidaVista.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_VISTA_ENTIDADPARTIDAVISTA_H_
#define SOURCE_VISTA_ENTIDADPARTIDAVISTA_H_

#include <string>
#include <iostream>
#include <typeinfo>
#include "../../Headers/Modelo/PicassoHelper.h"

namespace std {

class EntidadPartidaVista {
protected:
	int salud;
	pair<int,int> position;
	int width;
	int length;
	string sizeString;
	string pathImage;
	int id;

public:
	EntidadPartidaVista();
	virtual ~EntidadPartidaVista();
	void destruir();
	int getWidth();
	int getLength();
	string getPathImage();
	string getSizeString();
	void setPosition(int x,int y);
	void setPathImage(string path);
	pair<int,int>* getPosition();

	/*El objeto le dice a la vista que lo dibuje segun el tamaño que tenga la misma: 2x2,3x3,4x4,
	 *ya que el render depende de este factor*/
	virtual void drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos);
	void restarSalud();
};

} /* namespace std */

#endif /* SOURCE_MODELO_ENTIDADPARTIDAVISTA_H_ */
