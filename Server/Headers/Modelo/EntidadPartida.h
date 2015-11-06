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
#include "DefaultSettings.h"

namespace std {

class EntidadPartida {
protected:
	int health;
	int width;
	int length;
	int id;
	int visibilityRange;
	string name;
	pair<int,int> position;

public:
	EntidadPartida();
	int getWidth();
	int getLength();
	string getName();
	pair<int,int>* getPosition();
	int getVisibilityRange();
	int getId();
	void setPosition(int x,int y);
	void setName(string name);
	void setVisibilityRange(int range);
	/*
	*disminuye la salud de la entidad según 
	* */
	void subtractHealth(int attackValue);
	/*
	*establece la defenza de la entidad cuando lo están atacando
	* */
	int defend();
	virtual ~EntidadPartida();
};

} /* namespace std */

#endif /* SOURCE_MODELO_ENTIDADPARTIDA_H_ */
