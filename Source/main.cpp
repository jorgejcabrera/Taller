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
		JuegoVista* juegoVista = new JuegoVista(gController->getJuego());

		while(! gController->finDeJuego() && !salir ){
			//primero el controller actualiza el modelo
			gController->obtenerMouseInput();
			gController->actualizarJuego();

			//una vez actualizado el modelo la vista lo renderiza
			juegoVista->render();

			gController->delay();
			salir = gController->reiniciarJuego();

			if(salir)
				juegoTermina = false;

		}
		gController->~GameController();
		juegoVista->~JuegoVista();
	}
	return 0;
}

