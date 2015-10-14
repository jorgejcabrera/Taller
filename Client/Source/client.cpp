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

	/*MessageUpdate* message = new MessageUpdate(1,"DinamicEntity",0,1);
	string messageRead = message->getSerializeAsString();
	messageUpdate msg;
	msg.ParseFromString(messageRead);
	cout << msg.id()<< msg.tipo()<< msg.x()<<msg.y()<<endl;*/

	/*Client* jorge = new Client("127.0.0.1",7841);
	jorge->connectToServer();
	jorge->sendMessage(*(new MessageUpdate(1,"DinamicEntity",0,1)));*/


	Message* message1 = new Message(1,"DinamicEntity",0,1);
	cout << "El tamaño del mensaje1 es:" << message1->getSize()<<endl;
	Message* message2 = new Message(1,"Primer mensage de longitud va",0,1);
	cout << "El tamaño del mensaje2 es:" << message2->getSize()<<endl;

	//serializo
	char* buffer = message1->serializeToArray();
	//*(&buffer[message1->getSize()]) = message2->serializeToArray();

	//parseo
	msg_game msg;
	msg.ParseFromArray(buffer,message1->getSize());
	cout << msg.id()<< msg.tipo()<< msg.x()<<msg.y()<<endl;
	//muevo el puntero del buffer hasta donde empieza el proximo mensaje
	*buffer = buffer[message1->getSize()];
	buffer = message2->serializeToArray();
	msg.ParseFromArray(buffer,message2->getSize());
	Message mensage;
	mensage.setContent(msg);
	string elMensaje = mensage.toString();
	cout << elMensaje << endl;
	return 0;
}

