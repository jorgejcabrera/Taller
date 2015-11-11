/*
 * Juego.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_JUEGO_H_
#define SOURCE_MODELO_JUEGO_H_

#include "Mapa.h"
#include "EntidadDinamica.h"
#include "../Modelo/DefaultSettings.h"
#include "GameSettings.h"
#include "ResourceManager.h"
#include "PathFinder.h"
#include <map>
#include <list>


using namespace std ;

class Juego {
private:
	Mapa* mapa;
	/*
	* entidades dinámicas mapeadas por el owner
	* */
	map<int,EntidadDinamica*> protagonistas;
	/*
	* ?
	* */
	list<EntidadPartida*> newEntities;
	ResourceManager* resourseManager;
	GameSettings* gameSettings;

public:
	Juego();
	/*
	* intenta cargar la conf del yaml y setear los atributos al mapa, si por algún
	* motivo no los encuentra setea los valores por default
	* */
	Mapa* getMap();
	/*
	* establece la posición a donde va a moverse la entidad
	* */
	void setPlaceToGo(int idProtagonista, int x,int y);
	/*
	* le setea el target a la entidad pasada como parámetro, y su posición en ese instante
	* */
	void setTargetTo(int entityId,int target);
	/*
	* genera una entidad dinámica y se la asigna al jugador pasado como parámetro, devuelve el offset inicial del cliente
	* */
	pair<int,int> createEntitiesForClient(string owner, int clientIndex);
	/*
	*?
	* */
	void cleanNewEntities();
	/*
	* devuelve una lista de entidades que murieron
	* */
	list<EntidadDinamica> getFallenEntities();
	EntidadDinamica* getDinamicEntityById(int id);
	EntidadPartida* getEntityById(int id); // TODO reemplazar el anterior metodo por este
	/*
	 * Borro el personaje pasado por parametro, lo uso cuando el cliente de desconecto
	 */
	void deleteEntity(int id);
	ResourceManager* getResourceManager();
	map<int,EntidadDinamica*>* getDinamicEntities();
	list<EntidadPartida*>* getNewEntitiesToNotify();
	void createNewEntitie(string owner,string type, int idOfCreator);
	/*
	 * Creo al rey del jugador
	 */
	void createKingForClient(string owner);
	/*
	 * Obtengo la posicion del centro civico del jugador
	 */
	pair<int,int> getCivicCenterPositionOfClient(string owner);
	/*
	 * Creo la bandera para el jugador
	 */
	void createFlag(string client);
	pair<int,int> getNearestPositionOfABuilding(int idBuilding);
	virtual ~Juego();
};

#endif /* SOURCE_MODELO_JUEGO_H_ */
