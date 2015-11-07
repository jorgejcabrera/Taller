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
public:
	ResourceCounter();
	void recolectarOro();
	void recolectarMadera();
	void recolectarAlimento();
	void recolectar(string recurso);
	int getOro();
	int getAlimento();
	int getMadera();
	virtual ~ResourceCounter();
};

#endif /* RESOURCECOUNTER_H_ */
