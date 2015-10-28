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
#include <string>
#include <list>
using namespace std;

class ResourceManager {

private:
	Mapa* map;
	list<Resource*>* resources;
	int IdRecursoAEliminar;
	int oro;
	int madera;
	int alimento;
	bool notify;
	pair<int,int> posRecursoConsumido;
public:
	void collectResourceAt(pair<int,int>* pos);
	ResourceManager(Mapa* map);
	bool resourceAt(int x,int y);
	void actualizar();
	bool hasToNotify();
	void yaNotifique();
	pair<int,int> getPosRecursoConsumido();
	int getIdAEliminar();
	int getGold();
	int getWood();
	int getFood();
	virtual ~ResourceManager();
};

#endif /* RESOURCEMANAGER_H_ */
