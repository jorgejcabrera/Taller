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
using namespace std;

class ResourceManager {

private:
	Mapa* map;
	Resource* resource;
public:
	void collectResourceAt(pair<int,int>* pos);
	ResourceManager(Mapa* map);
	bool resourceAt(int x,int y);
	virtual ~ResourceManager();
};

#endif /* RESOURCEMANAGER_H_ */
