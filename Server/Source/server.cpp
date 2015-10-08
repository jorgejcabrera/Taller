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
#include "../Headers/Modelo/Server.h"
#include "../Headers/Modelo/PathFinder.h"


/*#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>*/


using namespace std;

int main(int argc, char* argv[]) {

	/*POR AHORA NO NOS INTERESA EL JUEGO SINO LA CONEXION DE SOCKET*/
	/*bool reiniciar = true;

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

		PathFinder* pf = new PathFinder(1,1,10,10,gController->getJuego()->getMap());
		pf->buscarCamino();

		juegoVista->~JuegoVista();
		gController->~GameController();
		delete(juegoVista);
		delete(gController);
		juegoVista=NULL;
		gController=NULL;
	}*/

	Server* server = new Server(7841);
	if( server->initSocketServer() == ERROR)
		cout<<"Error al inicializar socket"<<endl;
	server->listenClients();

	return 0;
}

