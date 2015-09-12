//============================================================================
// Name        : Taller.cpp
// Author      : Jorge
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/* Defines */
#define NUM_DOTS 1024

/* Includes */
#include <time.h>
#include "Vista/MapaVista.h"
#include "Vista/JuegoVista.h"
#include "Modelo/EntidadEstatica.h"
#include "Modelo/Mapa.h"
#include "Control/GameController.h"
#include <yaml.h>
#include "SDL2/SDL.h"

using namespace std;

int main(int argc, char* argv[]) {

	GameController* gController = new GameController();

	while(! gController->finDeJuego()){

		gController->obtenerMouseInput();
    	SDL_Delay(10);
	}

	std::cout<<"fin";
	return 0;
}

