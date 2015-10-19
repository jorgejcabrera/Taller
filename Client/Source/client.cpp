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
#include "../Headers/Modelo/Client.h"
#include "../Headers/Utils/Socket/Message.h"

#include <string>
#include <sstream>
#include <iostream>
#include <arpa/inet.h>
#include <stdint.h>


using namespace std;

int main(int argc, char* argv[]) {

	GameController* gController = new GameController();
	Client* jorge = new Client("127.0.0.1",7843, gController);
	jorge->connectToServer();


	//ESPERO 10 segundos
	SDL_Delay(5000);

	while( jorge->isConected() ){
		//leemos las novedades del server
		jorge->processReceivedMessages();

		//dibujammos el juego actualizado
		gController->actualizarJuego();
		gController->getJuegoVista()->render(gController->getRunCycles());

		//mandamos eventos al server
		jorge->sendEvents();
		gController->delay();
	}
	return 0;
}

