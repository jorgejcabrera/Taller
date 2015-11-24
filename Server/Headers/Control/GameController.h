/*
 * GameController.h
 *
 *  Created on: Sep 11, 2015
 *      Author: juan
 */

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "SDL2/SDL.h"
#include "../Modelo/Juego.h"
#include "../Modelo/GameSettings.h"
#include "../Modelo/DefaultSettings.h"
#include "../Control/UtilsController.h"
#include "../Utils/Socket/Message.h"
#include "../Modelo/EntidadPartida.h"
#include "../Modelo/EntidadDinamica.h"
#include <list>

enum game {
	CIVIC_CENTER,
	CAPTURE_FLAG,
	REGICIDE
};

class GameController {

private:
	UtilsController* utils;
	Juego* juego;
	GameSettings* gameSettings;
	bool gameRunning;
	int runCycles;
	int maxFramesPerSecond;
	int inicioDeCiclo;
	game gameType;

	void setNextPaths();
	/*
	* la entidad dinamica ataca o recolecta el recurso dependiendo del target
	* */
	void attackOrWork(EntidadDinamica* entity,EntidadPartida* target);
	/*
	* si las entidades tienen algun target, y éste se movió, se debe perseguirlo
	* */
	void pursuitAndAttackTarget(EntidadDinamica* attacker);
	/*
	* indica si la entidad pasada como parámetro está a la distancia necesaria del target para poder atacar
	* */
	bool readyToInteract(EntidadDinamica* entidad);
	/*
	* si el objetivo está demasiado lejos, ya no los podemos seguir
	* */
	bool targetOutOfReach(EntidadDinamica* entidad);
	/*
	* El target ya esta construido en totalidad
	* */
	bool targetCompleted(EntidadDinamica* entity);
	/*
	* si las entidades tiene algun target, interactuan con el, ya sea atacandolo o construyendolo
	* */
	void interactWithTargets();
	/*
	* La entidad construye el objetivo que tiene seteado
	* */
	void buildTarget(EntidadDinamica* builder);

public:
	GameController(string gameSelected);
	/*
	*defino un delay variable para poder mandarle los ms que yo quiera, mas que nada para el ciclo mientras espera clientes
	* */
	void delay(int ms);
	void updateGame();
	void delay();
	Juego* getJuego();
	int getRunCycles();
	int getMaxFramesPerSecond();
	list<Message*> getTilesMessages();
	list<Message*> getEntitiesMessages();
	list<int> getEntitiesOfClient(string userName);
	/*
	 * Verifica si el cliente perdió
	 */
	bool checkIfClientLostGame(string clientName);
	/*
	* Verifica si dentro de la lista de los personajes de un cliente existe uno que tenga name=king
	* Ver si queremos identificar al key de otra manera
	* */
	bool isKingOfClientAlive(string userName);
	/*
	* Verifica si el cliente aun tiene un centro civico
	* */
	bool isCivicCenterStillExist(string userName);
	/*
	* Verifica si el cliente aun tiene la bandera
	* */
	bool clientKeepFlag(string clienName);
	/*
	* devuelve true si el juego esta en curso o false si hay algun ganador
	* */
	bool isGameRunning();
	/*
	* Setea el gameRunning en false para indicar que ya termino el juego
	* */
	void gameFinished();
	/*
	* Crea las entidades del cliente
	* */
	pair<int,int> createEntitiesForClient(string owner, int clientIndex);
	virtual ~GameController();
};

#endif /* GAMECONTROLLER_H_ */
