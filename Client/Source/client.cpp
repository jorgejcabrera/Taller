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
#include "../Headers/Utils/Socket/MessageUpdate.h"


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

	//Message* message = new Message("este es mi mensaje");
	//char* messageRead = message->getSerializeMessage();

	Client* jorge = new Client("127.0.0.1",7841);
	jorge->connectToServer();
	/*jorge->sendMessage(*(new MessageUpdate(1,"DinamicEntity",0,1)));*/
	  return 0;
}

