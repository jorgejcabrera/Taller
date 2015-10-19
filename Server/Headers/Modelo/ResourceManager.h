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
#include "../Modelo/GameSettings.h"
#include <list>
using namespace std;

class ResourceManager {

private:
	Mapa* map;
	list<Resource*>* resources;
	int oro;
	int madera;
	int alimento;
public:
	void collectResourceAt(pair<int,int>* pos);
	ResourceManager(Mapa* map);
	bool resourceAt(int x,int y);
	void actualizar();
	int getGold();
	int getWood();
	int getFood();
	virtual ~ResourceManager();
};

#endif /* RESOURCEMANAGER_H_ */
