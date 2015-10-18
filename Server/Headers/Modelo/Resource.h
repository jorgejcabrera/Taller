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
public:
	Resource(int x,int y);
	void drawMe(pair<int,int> isometricPosition,int offX,int offY,int ciclos);
	bool isCollectable();
	virtual ~Resource();
};

#endif /* RESOURCE_H_ */
