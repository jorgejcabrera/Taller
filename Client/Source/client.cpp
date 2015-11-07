//============================================================================
// Name        : Taller.cpp
// Author      : Jorge
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

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
	Client* jorge = new Client(gController);
	//jorge->connectToServer("192.168.1.1");
	jorge->connectToServer("127.0.0.1");
	
	//delay to wait all messages from server
	SDL_Delay(9000);

	while( jorge->isConected() ){
		//leemos las novedades del server
		jorge->processReceivedMessages();
		gController->updateGame();
		//Si el juego no esta corriendo no actualizo la vista
		if(gController->gameIsRunning()){
			gController->getJuegoVista()->render(gController->getRunCycles(),jorge->getResourceCounter());
		}
		//escuchamos eventos y los mandamos al server
		jorge->sendEvents();
		jorge->verifyServerAlive();
		gController->delay();
	}
	jorge->~Client();
	//delete(jorge);
	delete(gController);
	return 0;
}

