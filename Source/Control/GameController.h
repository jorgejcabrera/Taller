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

class GameController {

private:
	SDL_Event* event;
	Juego* juego;
	JuegoVista* juegoVista;

	int posMouseX;
	int posMouseY;

	bool salirDelJuego;


public:
	GameController();
	void actualizarJuego();
	void render();
	void obtenerMouseInput();
	bool finDeJuego();
	virtual ~GameController();
};

#endif /* GAMECONTROLLER_H_ */
