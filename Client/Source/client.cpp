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
	int count = 0;

	while( jorge->isConected() && count < 4 ){
		cout << "cliente conectado"<<endl;
		jorge->sendMessage(*(new Message(1,"DinamicEntity",0,1)));
		count++;
	}
	//Logger::get()->log("[SocketUtils]","writeMessage"," ERROR writing to SocketUtils");

	return 0;
}

