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

	bool reiniciar = true;
	bool salir = false;


	while(reiniciar){
		reiniciar = false;
		GameController* gController = new GameController();
		JuegoVista* juegoVista = new JuegoVista(gController->getJuego());

		while(! gController->finDeJuego() && !reiniciar ){
			//primero el controller actualiza el modelo
			gController->obtenerMouseInput();
			gController->actualizarJuego();
			//una vez actualizado el modelo la vista lo renderiza
			juegoVista->render();
			gController->delay();
			reiniciar = gController->reiniciarJuego();

		}
		juegoVista->~JuegoVista();
		gController->~GameController();
	}
	return 0;
}

