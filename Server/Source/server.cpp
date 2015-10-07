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
#include "../Headers/Vista/JuegoVista.h"
#include "../Headers/Control/GameController.h"
#include "../Headers/Modelo/PathFinder.h"

using namespace std;


int main(int argc, char* argv[]) {

	bool reiniciar = true;

	while(reiniciar){
		reiniciar = false;
		GameController* gController = new GameController();
		JuegoVista* juegoVista = new JuegoVista(gController->getJuego());

		while(!gController->finDeJuego() && !reiniciar){
			//primero el controller actualiza el modelo
			gController->obtenerMouseInput();
			gController->actualizarJuego();
			//una vez actualizado el modelo la vista lo renderiza
			juegoVista->render(gController->getRunCycles());
			gController->delay();
			reiniciar = gController->reiniciarJuego();
		}

		//PathFinder* pf = new PathFinder(5,1,1,3,gController->getJuego()->getMap());
		//pf->buscarCamino();

//		juegoVista->~JuegoVista();
//		gController->~GameController();
		delete(juegoVista);
		delete(gController);
		juegoVista=NULL;
		gController=NULL;
		//delete server;
	}
	return 0;
}

