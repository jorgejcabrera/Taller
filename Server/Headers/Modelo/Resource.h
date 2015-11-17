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
public:
	Resource(string tipo,int x,int y);
	virtual ~Resource();
};

#endif /* RESOURCE_H_ */
