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
#include "../Headers/Control/GameController.h"
#include "../Headers/Modelo/Server.h"


using namespace std;

int main(int argc, char* argv[]) {

	/*POR AHORA NO NOS INTERESA EL JUEGO SINO LA CONEXION DE SOCKET*/
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

		PathFinder* pf = new PathFinder(0,0,0,5,gController->getJuego()->getMap());
		pf->buscarCamino();

		juegoVista->~JuegoVista();
		gController->~GameController();
		delete(juegoVista);
		delete(gController);
		juegoVista=NULL;
		gController=NULL;
	}*/

	GameController* gController = new GameController();
	Server* server = new Server(7843,gController);
	if( server->initSocketServer() == ERROR)
		cout<<"Error al inicializar socket"<<endl;
	server->start((void *) &server);
	cout << " YA START " <<endl;

	bool reiniciar = true;
	while(true){
		//Proceso las novedades de la cola del server y seteo la posicion de los protagonistas modificados
		server->processReceivedMessages();
		//Los protagonistas se trasladan a su posicion destino
		gController->actualizarJuego();
		//Se le manda a los clientes las novedades
		server->notifyClients();
		gController->delay();
		//reiniciar = gController->reiniciarJuego();
	}

	gController->~GameController();
	delete(gController);
	gController=NULL;
	cout << " YA TERMINE " <<endl;

	return 0;
}

