/*
 * GameController.h
 *
 *  Created on: Sep 11, 2015
 *      Author: juan
 */

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../Vista/JuegoVista.h"
#include "../Modelo/GameSettings.h"
#include "../Modelo/DefaultSettings.h"
#include "../Control/UtilsController.h"
#include "../Utils/Socket/Message.h"

class GameController {

private:
	UtilsController* utils;
	SDL_Event* event;
	JuegoVista* juegoVista;
	int posMouseX;
	int posMouseY;
	bool salirDelJuego;
	bool reiniciar;
	int runCycles;
	int maxFramesPerSecond;
	int inicioDeCiclo;
	GameSettings* gameSettings;
	pair<int,int> moveCharacter(int xScreen,int yScreen);
	pair<int,int> getOffset(int mouseX,int mouseY);

public:
	GameController();
	bool reiniciarJuego();
	void actualizarJuego();
	void render();
	Message* getMessageFromEvent(string userId);
	int getRunCycles();
	int getMaxFramesPerSecond();
	bool finDeJuego();
	virtual ~GameController();
	void delay();
};

#endif /* GAMECONTROLLER_H_ */
