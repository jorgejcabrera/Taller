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
	int posMouseX;
	int posMouseY;
	bool salirDelJuego;
	//TODO reiniciar juego no va mas
	bool reiniciar;
	int runCycles;
	int maxFramesPerSecond;
	int inicioDeCiclo;
	GameSettings* gameSettings;
	void setNextPaths();

public:
	GameController();
	Juego* getJuego();
	//TODO reiniciar juego no va mas
	bool reiniciarJuego();
	void actualizarJuego();
	int getRunCycles();
	int getMaxFramesPerSecond();
	virtual ~GameController();
	void delay();
	/*
	 * Defino un delay variable para poder mandarle los ms que yo quiera, mas que nada para el ciclo mientras espera clientes
	 */
	void delay(int ms);

	/*
	* generadores de mensajes para cuando se conecta un cliente nuevo
	* */
	list<Message*> getTilesMessages();
	list<Message*> getEntitiesMessages();
	list<int> getEntitiesOfClient(string userName);
};

#endif /* GAMECONTROLLER_H_ */
