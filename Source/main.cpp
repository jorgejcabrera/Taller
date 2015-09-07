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
#include "Modelo/Juego.h"
#include <yaml.h>

using namespace std;

int main(int argc, char* argv[]) {
	Juego* newJuego = new Juego();
	JuegoVista* juego = new JuegoVista();
	int count = 0;
	while(true){
		if(count == 10)
			break;
		count++;
    	SDL_Delay(500);
	}
	juego->~JuegoVista();
	return 0;
}

