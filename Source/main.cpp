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
#include "../Headers/Modelo/SocketServer.h"

using namespace std;

//hacmeos el llamado a server->run desde un hilo
SocketServer* server;
void* serverRun(void *){
	server->run();
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {

	/*server = new SocketServer;
	pthread_t hiloServer;
	pthread_create(&hiloServer,0,serverRun,NULL);
	pthread_detach(hiloServer);
	while(1){
		string message;
		cin >> message;
		server->setMensaje(message.c_str());
	}*/

	bool reiniciar = true;

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
//		juegoVista->~JuegoVista();
//		gController->~GameController();
		delete(juegoVista);
		delete(gController);
		juegoVista=NULL;
		gController=NULL;
		delete server;
	}
	return 0;
}

