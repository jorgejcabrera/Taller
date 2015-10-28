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
#include <stdio.h>
#include <unistd.h>
#include <ctime>

using namespace std;

/*int kbhit(){
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

void nonblock(int state){
    struct termios ttystate;
    int VMIN = 0;
    int ICANON = 0;
    int NB_ENABLE = 1;
    int NB_DISABLE = 0;
    int TCSANOW = 0;
    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);
 
    if (state==NB_ENABLE)
    {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    }
    else if (state==NB_DISABLE)
    {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
 
}*/

int main(int argc, char* argv[]) {

	GameController* gController = new GameController();
	Server* server = new Server(7843,gController);
	if( server->initSocketServer() == ERROR)
		return ERROR;
	server->start((void *) &server);
	/*int i = 0;
	nonblock(1);*/
	while(server->isRunning()){

		//Proceso las novedades de la cola del server y seteo la posicion de los protagonistas modificados
		server->processReceivedMessages();
		//Los protagonistas se trasladan a su posicion destino
		gController->actualizarJuego();
		server->setSeenTiles();
		//Se le manda a los clientes las novedades
		server->notifyClients();
		gController->delay();
		server->verifyClientsConections();
	}
	gController->~GameController();
	delete(gController);
	gController=NULL;
	server->~Server();
	return 0;
}

