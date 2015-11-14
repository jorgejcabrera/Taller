//============================================================================
// Name        : Taller.cpp
// Author      : Jorge
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


/* Includes */
#include "../Headers/Control/GameController.h"
#include "../Headers/Modelo/Server.h"
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(int argc, char* argv[]) {

	GameController* gController = new GameController();
	Server* server = new Server(7844,gController);
	if( server->initSocketServer() == ERROR)
		return ERROR;
	server->start((void *) &server);

	while(gController->isGameRunning()){
		server->verifyWaitingClients();
		//Proceso las novedades de la cola del server y seteo la posicion de los protagonistas modificados
		server->processReceivedMessages();
		//Los protagonistas se trasladan a su posicion destino
		gController->updateGame();
		server->setSeenTiles();
		//Se le manda a los clientes las novedades
		server->notifyClients();
		gController->delay();
		server->verifyClientsConections();
	}
	gController->~GameController();
	gController=NULL;
	server->~Server();
	return 0;
}

