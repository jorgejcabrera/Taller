/*
 * EntidadDinamica.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_ENTIDADDINAMICA_H_
#define SOURCE_MODELO_ENTIDADDINAMICA_H_

#include "EntidadPartida.h"
#include "../Utils/Logger.h"
#include "GameSettings.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <list>

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

class EntidadDinamica: public EntidadPartida {
private:
	list<pair<int,int> >* path;
	bool newPath;
	/*
	* necesario para sincronizar la parte visual en el cliente con la parte logica en el server
	* */
	bool readyToInteract;
	int ciclos;
	int cicloActual;
	/*
	* devuelve el daño causado al atacar
	* */
	int getDamage();

public:
	EntidadDinamica();
	EntidadDinamica(string nameEntity, int vel,float posX,float posY, float width, float length);
	/*
	* devuelve true si pudo mover la entidad de posicion
	* */
	void nextPosition();
	/*
	* devuelve el camino que debe recorrer la entidad para llegar a la posicion deseada
	* */
	list<pair<int,int> >* getPath();
	/*
	* disminuye la salud de la entidad según 
	* */
	void attackTo();
	void setPathIsNew(bool esNuevo);
	void setPath(list<pair<int,int> >* camino);
	void prepareToInteract(bool value);
	bool isReadyToInteract();
	bool pathIsNew();
	bool isMoving();
	pair<int,int> getPositionToGo();
	pair<int,int> getNextPosition();
	/*
	* aumenta la salud del edicicio
	* */
	void construct(EntidadPartida* entity);
	virtual ~EntidadDinamica();
};

#endif /* SOURCE_MODELO_ENTIDADDINAMICA_H_ */
