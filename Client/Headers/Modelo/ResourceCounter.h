/*
 * ResourceCounter.h
 *
 *  Created on: Oct 28, 2015
 *      Author: juan
 */

#ifndef RESOURCECOUNTER_H_
#define RESOURCECOUNTER_H_

#include <string>

using namespace std;

class ResourceCounter {
private:
	int oro;
	int madera;
	int alimento;
	int roca;
public:
	ResourceCounter();
	void gastar(string recurso);
	void increase(string recurso,int quantity);
	int getGold();
	int getFood();
	int getWood();
	int getRock();
	virtual ~ResourceCounter();
};

#endif /* RESOURCECOUNTER_H_ */
