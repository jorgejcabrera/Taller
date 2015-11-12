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
	bool caminando;
	//bool notifiable;
	bool newPath;
	int ciclos;
	int cicloActual;

public:
	EntidadDinamica();
	EntidadDinamica(string nameEntity, int vel,float posX,float posY, float width, float length);
	void setPath(list<pair<int,int> >* camino);
	/*
	* devuelve true si pudo mover la entidad de posicion
	* */
	void nextPosition();
	/*
	*
	* */
	list<pair<int,int> >* getPath();
	bool isWalking();
	void setNotifiable(bool notifiable);
	void setPathIsNew(bool esNuevo);
	bool pathIsNew();
	bool hasToNotify();
	virtual ~EntidadDinamica();
};

#endif /* SOURCE_MODELO_ENTIDADDINAMICA_H_ */
