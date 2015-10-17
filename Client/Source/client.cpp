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
		delete(juegoVista);
		delete(gController);
		juegoVista=NULL;
		gController=NULL;
		//delete server;
	}*/

	Message* unMensaje = new Message();
	msg_game msg;
	msg.set_id(1);
	msg.set_tipo("unTipo");
	msg.set_x(10);
	msg.set_y(10);
	unMensaje->setContent(msg);

	cout << "El tamaño del mensaje es: "<< unMensaje->getSize()-4 << endl;

	char* msgSerializado = unMensaje->serializeToArray();
	cout <<"Del buffer obtuve: "<< msgSerializado[0]<<endl;




	/*Client* jorge = new Client("127.0.0.1",7843);
	jorge->connectToServer();
	int count = 0;

	while(jorge->isConected() && count < 4){
		cout << "Client is sending message"<<endl;
		jorge->sendMessage(*(new Message(1,"DinamicEntity",0,1)));
		count++;
	}*/
	return 0;
}

