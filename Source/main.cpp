//============================================================================
// Name        : Taller.cpp
// Author      : Jorge
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//http://www.dreamincode.net/forums/topic/290187-linux-game-programming-tutorial-1-introduction-first-sdl/

/* Defines */
#define NUM_DOTS 1024

/* Includes */
#include <time.h>
#include "Vista/MapaVista.h"
#include "Vista/JuegoVista.h"
#include "Modelo/EntidadEstatica.h"
#include <yaml.h>

using namespace std;

int main(int argc, char* argv[]) {
	JuegoVista* juego = new JuegoVista();
	int count = 0;
	while(true){
		if(count == 10000000)
			break;
		count++;
    	SDL_Delay(100000000000);
	}
	juego->~JuegoVista();
	return 0;
}

