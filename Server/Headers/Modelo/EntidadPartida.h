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
#include "../Utils/ResourceCounter.h"
#include "../Utils/Socket/Message.h"
#include "DefaultSettings.h"

using namespace std;

class EntidadPartida {
protected:
	/*
	* utilizado para decir que está completamente construido
	* */
	bool isCompleted;
	pair<int,int> position;
	int width;
	int length;
	int id;
	int visibilityRange;
	string name;
	string owner;
	/*
	* atributo para saber la entidada sufrió algún cambio y debe ser notificado su status
	* */
	bool notifiable;
	/*
	* parametros variables segun el nivel y características de la entidad
	* */
	int health;
	int maxHealth;
	int strength;
	float precision;
	int builderEffort;
	/*
	* id de la entidad con la que se va a interactuar, por ejemplo a atacar
	* */
	EntidadPartida* target;
	/*
	* establece la defenza de la entidad cuando lo están atacando
	* */
	int defend();
	/*
	* userName dueño de la entidad que ataco por ultima vez
	* */
	string attacker;

public:
	EntidadPartida();
	/*
	* geters
	* */
	int getWidth();
	int getLength();
	int getVisibilityRange();
	int getId();
	int getHealth();
	int getStrength();
	float getPrecision();
	string getName();
	string getOwner();
	string getAttacker();
	pair<int,int> getPosition();
	list<pair<int,int> > getNearestPositions();
	EntidadPartida* getTarget();
	Message* getMessage();
	/*
	* seters
	* */
	void setTarget(EntidadPartida* target);
	void setPosition(int x,int y);
	void setHealth(int health);
	void setStrength(int strength);
	void setPrecision(float presition);
	void setBuilderEffort(int effort);
	void setName(string name);
	void setVisibilityRange(int range);
	void setNotifiable(bool notifiable);
	void setOwner(string owner);
	/*
	* la entidad recibe el daño provocado y el userName dueño del atacante y descuenta salud
	* */
	void takeDamage(int damage, string attarckerId);
	/*
	* la entidad recibe el efuerzo aplicado a la construccion
	* */
	void takeBuilderEffort(int effort);
	/*
	* si la entidad sufrio algun cambio debe ser notificado
	* */
	bool hasToNotify();
	/*
	* analiza si la salud esta al maximo
	* */
	bool isMaxHealth();
	/*
	 *
	 */
	bool isConstructionCompleted();
	void completeConstruction();
	virtual ~EntidadPartida();
};

#endif /* SOURCE_MODELO_ENTIDADPARTIDA_H_ */
