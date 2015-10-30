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
	int IdNuevoRecurso;
	int oro;
	int madera;
	int alimento;
	bool notify;
	bool newResource;
	pair<int,int> posNuevoRecurso;
	string ultimoEnConsumir;
	string ultimoTipoConsumido;
	string tipoUltimoCreado;
public:
	void collectResourceAt(pair<int,int>* pos);
	ResourceManager(Mapa* map);
	bool resourceAt(int x,int y);
	void actualizar();
	bool hasToNotify();
	void yaNotifique();
	bool hasNewResource();
	void newResourceSent();
	pair<int,int> getPosNuevoRecurso();
	//setea el ultimo usuario en consumir un recurso
	void setUltimoEnConsumir(string owner);
	string getUltimoEnConsumir();
	//setea el ultimo tipo consumido (madera,oro o alimento)
	void setUltimoTipoConsumido(string tipo);
	string getUltimoTipoConsumido();
	string getUltimoTipoCreado();

	int getIdAEliminar();
	int getIdNuevoRecurso();
	int getGold();
	int getWood();
	int getFood();
	virtual ~ResourceManager();
};

#endif /* RESOURCEMANAGER_H_ */
