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

//namespace std {

using namespace std;

class EntidadPartidaVista {
protected:
	pair<int,int> position;
	int width;
	int length;
	string sizeString;
	string pathImage;
	int id;
	string name;
	bool seen;
	string owner;

private:
	int salud;

public:
	EntidadPartidaVista();
	int getWidth();
	int getLength();
	string getPathImage();
	string getSizeString();
	void setPosition(int x,int y);
	void setPathImage(string path);
	pair<int,int>* getPosition();
	void setId(int identifier);
	int getId();
	void setName(string name);
	string getName();
	int getSalud();
	/*
	*El objeto le dice a la vista que lo dibuje segun el tamaño que tenga la misma: 1x1,2x2,3x3,
	*4x4 ya que el render depende de este factor
	**/
	virtual void drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos);
	bool getSeen();
	void saw();

	void setOwner(string owner);
	string getOwner();
	virtual ~EntidadPartidaVista();
};

//} /* namespace std */

#endif /* SOURCE_MODELO_ENTIDADPARTIDAVISTA_H_ */
