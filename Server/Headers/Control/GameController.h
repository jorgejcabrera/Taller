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
	REGICIDE} ;

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
	* si las entidades tiene algun target, y éste se movió, se debe perseguirlo
	* */
	void pursuitAndAttackTarget();
	/*
	* indica si la entidad pasada como parámetro está a la distancia necesaria del target para poder atacar
	* */
	bool readyToAttack(EntidadDinamica* entidad);
	/*
	* si el objetivo está demasiado lejos, ya no los podemos seguir
	* */
	bool targetOutOfReach(EntidadDinamica* entidad);

public:
	GameController();
	/*
	*defino un delay variable para poder mandarle los ms que yo quiera, mas que nada para el ciclo mientras espera clientes
	* */
	void delay(int ms);
	/*
	*generadores de mensajes para cuando se conecta un cliente nuevo
	* */
	Juego* getJuego();
	void updateGame();
	int getRunCycles();
	int getMaxFramesPerSecond();
	void delay();
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
	 */
	bool isKingOfClientAlive(string userName);
	/*
	 * Verifica si el cliente aun tiene un centro civico
	 */
	bool isCivicCenterStillExist(string userName);
	/*
	 * devuelve true si el juego esta en curso o false si hay algun ganador
	 */
	bool isGameRunning();
	/*
	 * Setea el gameRunning en false para indicar que ya termino el juego
	 */
	void gameFinished();
	virtual ~GameController();
};

#endif /* GAMECONTROLLER_H_ */
