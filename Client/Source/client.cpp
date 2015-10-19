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
	jorge->sendMessage(new Message(115,"personajes",20,20));

	//ESPERO 25 segundos
	SDL_Delay(25000);
	cout << "YA TERMINE" << endl;

	return 0;
}

