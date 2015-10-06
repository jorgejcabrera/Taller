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

using namespace std;

bool readFull(int sock, char *buffer, size_t size)
{
  size_t received = 0;
  while (received < size)
  {
    ssize_t r = read(sock, buffer + received, size - received);
    if (r <= 0) break;
    received += r;
  }
  cout<<"CLI Respuesta recibida: "<<buffer<<endl;
  return received == size;
}

bool writeFull(int cliente, char *buffer, size_t size, const char *msg)
{
	strcpy(buffer,msg);
	ssize_t n=write(cliente,buffer,size);
	if(n < 0) cout<<"CLI ERROR writing to socket"<<endl;
	return (n<0);
}

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
	  /*int cliente;
	  const char *ip="127.0.0.1";
	  int puerto = 7891;
	  int bufsize = 1024;
	  char buffer[bufsize];
	  struct sockaddr_in serverAddr;

	  if((cliente = socket(PF_INET,SOCK_STREAM,0))<0){
	    cout << "CLI Error al crear el socket cliente"<<endl;
	    exit(0);
	  }
	  cout<<"CLI Socket creado"<<endl;
	  serverAddr.sin_family = AF_INET;
	  serverAddr.sin_port = htons(puerto);
	  serverAddr.sin_addr.s_addr = inet_addr(ip);

	  if(connect(cliente,(struct sockaddr *)&serverAddr,sizeof(serverAddr))==0)
	    cout<<"CLI Conexion con el servidor "<<inet_ntoa(serverAddr.sin_addr)<<endl;
	  cout<<"CLI Esperando confirmacion del servidor"<<endl;
	  readFull(cliente,buffer,bufsize);
	  writeFull(cliente,buffer,bufsize,"CLI mensaje del CLIENTE AGE OF EMPIRES");
	  readFull(cliente,buffer,bufsize);
	  cout<<"CLI Conexion terminada. Programa finalizado\n\n";
	  close(cliente);*/

	Client* jorge = new Client("127.0.0.1",7841);
	jorge->connectToServer();
	  return 0;
}

