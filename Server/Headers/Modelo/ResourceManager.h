/*
 * ResourceManager.h
 *
 *  Created on: Oct 17, 2015
 *      Author: juan
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "../Modelo/Mapa.h"
#include "../Modelo/Resource.h"
#include <list>
using namespace std;

class ResourceManager {

private:
	Mapa* map;
	list<Resource*>* resources;
public:
	void collectResourceAt(pair<int,int>* pos);
	ResourceManager(Mapa* map);
	bool resourceAt(int x,int y);
	virtual ~ResourceManager();
};

#endif /* RESOURCEMANAGER_H_ */
