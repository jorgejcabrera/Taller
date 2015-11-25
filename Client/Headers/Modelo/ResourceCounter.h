/*
 * ResourceCounter.h
 *
 *  Created on: Oct 28, 2015
 *      Author: juan
 */

#ifndef RESOURCECOUNTER_H_
#define RESOURCECOUNTER_H_
#define INIT_CANT 10000;

#include <string>
#include "DefaultSettings.h"

using namespace std;

class ResourceCounter {
private:
	int gold;
	int wood;
	int food;
	int rock;
public:
	ResourceCounter();
	void gastar(string recurso);
	void increase(string recurso,int quantity);
	void refund(string type);
	int getGold();
	int getFood();
	int getWood();
	int getRock();
	virtual ~ResourceCounter();
};

#endif /* RESOURCECOUNTER_H_ */
