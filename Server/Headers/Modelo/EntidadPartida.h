/*
 * EntidadPartida.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_ENTIDADPARTIDA_H_
#define SOURCE_MODELO_ENTIDADPARTIDA_H_

#include <string>
#include <iostream>
#include <typeinfo>
#include "../Utils/SequenceUtils.h"

namespace std {

class EntidadPartida {
protected:
	int salud;
	pair<int,int> position;
	int width;
	int length;
	string sizeString;
	string name;
	int id;
	int rangeVisibility;

public:
	EntidadPartida();
	virtual ~EntidadPartida();
	void destruir();
	int getWidth();
	int getLength();
	string getName();
	string getSizeString();
	void setPosition(int x,int y);
	void setName(string name);
	pair<int,int>* getPosition();
	int getId();
	void setRangeVisibility ( int range);
	int getRangeVisibility();

	/*El objeto le dice a la vista que lo dibuje segun el tamaño que tenga la misma: 2x2,3x3,4x4,
	 *ya que el render depende de este factor*/
	void restarSalud();
};

} /* namespace std */

#endif /* SOURCE_MODELO_ENTIDADPARTIDA_H_ */
