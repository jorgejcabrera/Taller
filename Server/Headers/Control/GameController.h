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
#include "../Utils/Socket/MessageUpdate.h"

class GameController {

private:
	UtilsController* utils;
	Juego* juego;
	int posMouseX;
	int posMouseY;
	bool salirDelJuego;
	bool reiniciar;
	int runCycles;
	int maxFramesPerSecond;
	int inicioDeCiclo;
	GameSettings* gameSettings;
	void moveCharacter(int xScreen,int yScreen);
	pair<int,int> getOffset(int mouseX,int mouseY);

public:
	GameController();
	Juego* getJuego();
	bool reiniciarJuego();
	void actualizarJuego();
	int getRunCycles();
	int getMaxFramesPerSecond();
	virtual ~GameController();
	void delay();
	list<MessageUpdate*> getTilesMessages();
};

#endif /* GAMECONTROLLER_H_ */
