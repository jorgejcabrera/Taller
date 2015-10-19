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

	Client* jorge = new Client("127.0.0.1",7843);
	jorge->connectToServer();
	GameController* gController = new GameController();

	//ESPERO 10 segundos
	SDL_Delay(10000);

	while( jorge->isConected() ){
		//leemos las novedades del server
		jorge->processReceivedMessages();

		//dibujammos el juego actualizado
		gController->actualizarJuego();

		//mandamos eventos al server
		jorge->sendEvents();
	}
	return 0;
}

