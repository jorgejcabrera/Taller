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
	pair<int,int> position;
	/*
	* posicion de la entidad marcada como objetivo
	* */
	pair<int,int> targetPosition;
	int width;
	int length;
	int id;
	int visibilityRange;
	string name;
	string owner;
	/*
	* parametros variables segun el nivel y características de la entidad
	* */
	int health;
	int strength;
	float precision;
	/*
	* id de la entidad con la que se va a interactuar, por ejemplo a atacar
	* */
	int target;
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
	int getTarget();
	int getVisibilityRange();
	int getId();
	int getHealth();
	int getStrength();
	float getPrecision();
	string getName();
	pair<int,int> getTargetPosition();
	pair<int,int> getPosition();
	void setTarget(int target);
	void setPosition(int x,int y);
	void setHealth(int health);
	void setStrength(int strength);
	void setPrecision(float presition);
	void setTargetPosition(pair<int,int> position);
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
	/*
	* seteo el dueño de la entidad
	* */
	void setOwner(string owner);
	/*
	* Devuelvo el nombre del cliente dueño de la entidad
	* */
	string getOwner();
	virtual ~EntidadPartida();
};

#endif /* SOURCE_MODELO_ENTIDADPARTIDA_H_ */
