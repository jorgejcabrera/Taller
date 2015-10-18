/*
 * Resource.h
 *
 *  Created on: Oct 17, 2015
 *      Author: juan
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include "EntidadEstatica.h"

class Resource: public EntidadEstatica {
private:
	string tipo;
public:
	Resource(string tipo,int x,int y);
	string getTipo();
	void drawMe(pair<int,int> isometricPosition,int offX,int offY,int ciclos);
	virtual ~Resource();
};

#endif /* RESOURCE_H_ */
