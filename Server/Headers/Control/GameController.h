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

class GameController {

private:
	UtilsController* utils;
	Juego* juego;
	GameSettings* gameSettings;
	bool salirDelJuego;
	int runCycles;
	int maxFramesPerSecond;
	int inicioDeCiclo;
	void setNextPaths();
	/*
	* si las entidades tiene algun target, y éste se movió, se debe perseguirlo
	* */
	void pursuitTarget();

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
	virtual ~GameController();
};

#endif /* GAMECONTROLLER_H_ */
