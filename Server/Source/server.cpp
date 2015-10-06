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
#include "../Headers/Modelo/Server.h"
#include "../Headers/Modelo/PathFinder.h"


#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


using namespace std;

bool writeFull(int servidor, char *buffer, size_t size, const char *msg){
	strcpy(buffer,msg);
	ssize_t n=write(servidor,buffer,size);
	if(n < 0) cout<<"SRV ERROR writing to socket"<<endl;
	return (n<0);
}

bool readFull(int sock, char *buffer, size_t size){
  size_t received = 0;
  while (received < size){
    ssize_t r = read(sock, buffer + received, size - received);
    if (r <= 0) break;
    received += r;
  }
  return received == size;
}

int main(int argc, char* argv[]) {

	/*POR AHORA NO NOS INTERESA EL JUEGO SINO LA CONEXION DE SOCKET*/
	/*bool reiniciar = true;

	PathFinder* pf = new PathFinder(2,2,5,7);
	pf->buscarCamino();

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
	}*/

	/*creamos el servidor*/

//	int clientes, servidor;
//	int portNum = 7891;										//acá va el puerto por el que nos vamos a comunicar
//	int bufsize = 1024;
//	char buffer[bufsize];//son los char que vamos a mandar con las funciones send y recv
//
//	struct sockaddr_in serverAddr;
//	memset(&serverAddr,0,sizeof(serverAddr));
//	socklen_t tamano;
//
//	//init socket
//	if( (clientes = socket(PF_INET, SOCK_STREAM, 0)) < 0 ){	//creamos el socket dominio: AF_INET (Protocolo TCP)
//		cout << "SRV Error al crear el socket"<<endl;
//		exit(1);
//	}
//	cout << "SRV Socket servidor ha sido creado..."<< endl;
//
//
//	serverAddr.sin_family = AF_INET;								//asignamos a la estructura sockaddr_in un dominio, una ip y un puerto
//	//serverAddr.sin_addr.s_addr = htons(INADDR_ANY);				//INADDR_ANY es asignarle automaticamente la serverAddrcion local
//	serverAddr.sin_port = htons(portNum);						//sin_addr y sin_port deben convertirse a Network byte y para ello usamos htons o htonl
//
//	//binding socket
//	if(bind(clientes, (struct sockaddr*)&serverAddr,sizeof(serverAddr)) < 0){	//bind: crea la conexion con el puerto y el socket creado (clientes)
//		cout << "SRV Error en la conexion bind..."<<endl;				//clientes: es el socket a conectar, &serverAddr es una estructura donde
//		exit(1);													//guardamos la ip local y el puerto, tamano de la estrucrura serverAddr
//	}
//
//	tamano = sizeof(serverAddr);
//	cout << "SRV Esperando clientes..."<<endl;
//
//	//listing socket
//	listen(clientes, 1);									//esta funcion escucha si algun cliente se quiere conectar, y el segundo parametro
//															//es el numero de clientes en cola
//
//	while((servidor = accept(clientes,(struct sockaddr*)&serverAddr,&tamano))>0){	//aceptamos la conexion retorna negativo si falla
//		writeFull(servidor,buffer,bufsize,"SRV Servidor conectado");
//		cout<<"SRV Conexion con el cliente EXITOSA"<<endl;
//		readFull(servidor,buffer,bufsize);
//		cout << "SRV Mensaje recibido SERVER: "<<buffer<< endl;
//		writeFull(servidor,buffer,bufsize,"SRV mensaje del SERVER");
//		cout << "SRV El servidor termino la conexion con " <<inet_ntoa(serverAddr.sin_addr)<<endl;
//		close(servidor);
//		cout << "SRV Conecte nuevo cliente."<<endl;
//	}
//
//	close(clientes);	//cerramos el socket

	Server* server = new Server(7841);
	if( server->initSocketServer() == ERROR)
		cout<<"Error al inicializar socket"<<endl;


	return 0;
}

