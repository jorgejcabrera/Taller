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
#include "Vista/JuegoVista.h"
#include "Modelo/EntidadEstatica.h"
#include "Modelo/Mapa.h"
#include "Control/GameController.h"
#include <yaml.h>
#include "SDL2/SDL.h"


using namespace std;


int main(int argc, char* argv[]) {

	bool juegoTermina = false;
	bool salir = false;

	while(!juegoTermina){
		juegoTermina = true;
		salir = false;
		GameController* gController = new GameController();

		while(! gController->finDeJuego() && !salir ){
			gController->obtenerMouseInput();
			gController->actualizarJuego();
			gController->render();
			gController->delay();

			salir = gController->reiniciarJuego();

			if(salir)
				juegoTermina = false;

		}
		gController->~GameController();
	}
	return 0;
}

