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
#include "../Modelo/GameSettings.h"

using namespace std;

enum Direccion{
	Norte,
	Noreste,
	Este,
	Sureste,
	Sur,
	Suroeste,
	Oeste,
	Noroeste,
	Sindireccion
};

class EntidadPartidaVista {
protected:
	bool isCompleted;
	pair<int,int> position;
	int id;
	int width;
	int length;
	string sizeString;
	string pathImage;
	string name;
	string owner;
	bool seen;
	/*
	* id de la entidad con la que se va a interactuar, por ejemplo a atacar
	* */
	EntidadPartidaVista* target;
	/*
	* parametros variables segun el nivel y características de la entidad
	* */
	int health;
	int maxHealth;
	int strength;
	float precision;

public:
	EntidadPartidaVista();
	int getWidth();
	int getLength();
	int getId();
	int getHealth();
	int getStrength();
	float getPrecision();
	string getName();
	string getOwner();
	string getPathImage();
	string getSizeString();
	bool getSeen();
	pair<int,int> getPosition();
	EntidadPartidaVista* getTarget();
	/*
	* retorna la posición con la que quedo orientada la entidad al llegar al target
	* */
	Direccion getStandigDirection();
	void setOwner(string owner);
	void setName(string name);
	void setPosition(int x,int y);
	void setPathImage(string path);
	void setId(int identifier);
	void setTarget(EntidadPartidaVista* target);
	void setHealth(int health);
	void setStrength(int strength);
	void setPrecision(float presition);
	/*
	* El objeto le dice a la vista que lo dibuje segun el tamaño que tenga la misma: 1x1,2x2,3x3,
	* 4x4 ya que el render depende de este factor
	* */
	virtual void drawMe(pair<int,int> isometricPosition, pair<int,int>* offSet, int ciclos);
	void saw();
	bool isBuildingCompleted();
	void setBuildingCompleted(bool completed);
	bool isUnderAttack();
	virtual ~EntidadPartidaVista();
};

#endif /* SOURCE_MODELO_ENTIDADPARTIDAVISTA_H_ */
