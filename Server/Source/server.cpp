//============================================================================
// Name        : Taller.cpp
// Author      : Jorge
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


/* Includes */
#include "../Headers/Control/GameController.h"
#include "../Headers/Vista/LoginVista.h"
#include "../Headers/Modelo/Server.h"
#include <stdlib.h>
#include <string.h>
//#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
	LoginVista* loginVista = new LoginVista();
	string gameType = loginVista->askGameType();
	int clientsQty = loginVista->askClientsNumber();
	int port = loginVista->askPort();
	cout << "Partida: "<< gameType << " cantidad: " <<clientsQty<< " Puerto: "<< port<<endl;
	loginVista->~LoginVista();

	GameController* gController = new GameController(gameType);
	Server* server = new Server(port,gController, clientsQty);
	if( server->initSocketServer() == ERROR)
		return ERROR;
	server->start((void *) &server);
	cout << "SERVER is RUNNING"<< endl;
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

