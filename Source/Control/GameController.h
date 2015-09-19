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
#include "../Modelo/Juego.h"
#include "../Vista/JuegoVista.h"
#include "../Modelo/DefaultSettings.h"
#include "../Control/UtilsController.h"

class GameController {

private:
	UtilsController* utils;
	SDL_Event* event;
	Juego* juego;
	int posMouseX;
	int posMouseY;
	bool salirDelJuego;
	bool reiniciar;
	int inicioDeCiclo;
	void moveCharacter(int xScreen,int yScreen);
	pair<int,int> getOffset(int mouseX,int mouseY);

public:
	GameController();
	Juego* getJuego();
	bool reiniciarJuego();
	void actualizarJuego();
	void render();
	void obtenerMouseInput();
	bool finDeJuego();
	virtual ~GameController();
	void delay();
};

#endif /* GAMECONTROLLER_H_ */
