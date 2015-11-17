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
	int beforeQuantity;
public:
	Resource(string tipo,int x,int y);
	void takeDamage(int damage, string attarckerId);
	int getAmountCollected();
	virtual ~Resource();
};

#endif /* RESOURCE_H_ */
