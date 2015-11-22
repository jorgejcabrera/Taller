/*
 * Juego.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_JUEGO_H_
#define SOURCE_MODELO_JUEGO_H_
#define OK 1
#define ERROR 0

#include "Mapa.h"
#include "EntidadDinamica.h"
#include "../Modelo/DefaultSettings.h"
#include "GameSettings.h"
#include "PathFinder.h"
#include <map>
#include <list>


using namespace std ;

class Juego {
private:
	Mapa* mapa;
	GameSettings* gameSettings;
	/*
	* entidades dinámicas mapeadas por el owner
	* */
	map<int,EntidadDinamica*> protagonistas;
	/*
	* lista de entidades que deben ser notificadas porque sufrieron algún cambio
	* */
	list<EntidadPartida*> newEntities;
	/*
	* habilita los tiles ocupados por la entidad pasada como parametro una vez que se elimina
	* */
	void enableTiles(EntidadPartida* entity);

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
	list<EntidadPartida> getFallenEntities();
	EntidadDinamica* getDinamicEntityById(int id);
	EntidadPartida* getEntityById(int id); // TODO reemplazar el anterior metodo por este
	/*
	* Borro el personaje pasado por parametro, lo uso cuando el cliente de desconecto
	* */
	void deleteEntity(int id);
	map<int,EntidadDinamica*>* getDinamicEntities();
	list<EntidadPartida*>* getNewEntitiesToNotify();
	int createNewEntitie(string owner,string type, int idOfCreator);
	/*
	* Creo al rey del jugador
	* */
	void createKingForClient(string owner);
	/*
	* Obtengo la posicion del centro civico del jugador
	* */
	pair<int,int> getCivicCenterPositionOfClient(string owner);
	/*
	* Creo la bandera para el jugador
	* */
	void createFlag(string client);
	/*
	* Obtengo una posicion dentro del perimetro del edificio,
	* si no hay ninguna disponible, llama a mapa->getAvailablePosition(x,y)
	* */
	pair<int,int> getNearestPosition(EntidadPartida* entity);
	/*
	* Dados dos usuarios traspasa todas las entidades del ownerFrom al ownerTo y lo agrega en la lista newEntities para que se notifiquen
	* */
	void transferEntitiesToUser(string userFrom, string userTo);
	/*
	* construye un edificio
	* */
	int buildEntity(string nameEntity, int positionX, int positionY, string owner);
	/*
	* Agrego una entidad para notificar
	* */
	void addNewEntity(EntidadPartida* entity);
	virtual ~Juego();
};

#endif /* SOURCE_MODELO_JUEGO_H_ */
