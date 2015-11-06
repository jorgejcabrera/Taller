/*
 * EntidadPartida.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_ENTIDADPARTIDA_H_
#define SOURCE_MODELO_ENTIDADPARTIDA_H_
#define ARC4RANDOM_MAX	0x100000000

#include <string>
#include <iostream>
#include <typeinfo>
#include "../Utils/SequenceUtils.h"
#include "DefaultSettings.h"

using namespace std;

class EntidadPartida {
protected:
	int visibilityRange;
	string name;
	pair<int,int> position;
	int width;
	int length;
	int id;
	/*
	* parametros variables segun el nivel y características de la entidad
	* */
	int health;
	int strength;
	float precision;
	/*
	* devuelve el daño causado al atacar
	* */
	int getDamage();
	/*
	* establece la defenza de la entidad cuando lo están atacando
	* */
	int defend();

public:
	EntidadPartida();
	int getWidth();
	int getLength();
	int getHealth();
	string getName();
	pair<int,int>* getPosition();
	int getVisibilityRange();
	int getId();
	void setPosition(int x,int y);
	void setName(string name);
	void setVisibilityRange(int range);
	/*
	* disminuye la salud de la entidad según 
	* */
	void attackTo(EntidadPartida* entity);
	/*
	* la entidad recibe el daño provoca y descuenta salud
	* */
	void takeDamage(int damage);
	virtual ~EntidadPartida();
};

#endif /* SOURCE_MODELO_ENTIDADPARTIDA_H_ */
