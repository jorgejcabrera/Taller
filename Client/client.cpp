/*
 * Server.cpp
 *
 *  Created on: 28 de set. de 2015
 *      Author: jorge
 */

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;

//el cliente necesita saber el puerto del servidor
int main(){
	char a;
	int cliente;
	int puerto = 1500;
	int bufsize = 1024;
	char* buffer = new char (bufsize);
	bool salir = false;
	char* ip;
	strcpy(ip,"127.0.0.1");

	struct sockaddr_in direc;

	if((cliente = socket(AF_INET,SOCK_STREAM,0))<0){
		cout << "Error al crear el socket cliente"<<endl;
		exit(0);
	}

	cout << "Escriba # para acabar la comunicacion"<<endl;
	cout << "\t\t\t[s] para empezar"<<endl;
	cin>>a;

	cout<<"Socket creado"<<endl;
	direc.sin_family = AF_INET;
	direc.sin_port = htons(puerto);
	inet_pton(AF_INET,ip,&direc.sin_addr);

	if(connect(cliente,(struct sockaddr *)&direc,sizeof(direc))==0)
		cout<<"Conexion con el servidor "<<inet_ntoa(direc.sin_addr)<<endl;

	cout<<"Esperando confirmacion del servidor"<<endl;
	recv(cliente,buffer,bufsize,0);

	cout<<"Respuesta recibida: "<<buffer;
	cout<<"\nRecuerde poner el asterisco al final para mandar un mensaje *\nEscriba # para terminar la conexion"<<endl;

	do{
		cout<<"Escribir un mensaje: ";
		do{
			cin>>buffer;
			send(cliente,buffer,bufsize,0);
			if(*buffer == '#'){
				send(cliente,buffer,bufsize,0);
				*buffer = '*';
				salir = true;
			}
		}while(*buffer != 42);

		cout<<"Mensaje recibido: ";
		do{
			recv(cliente,buffer,bufsize,0);
			cout<<buffer<<" ";
			if(*buffer == '#'){
				*buffer = '*';
				salir = true;
			}
		}while(*buffer != 42);
		cout << endl;
	}while(!salir);
	cout<<"Conexcion terminada. Programa finalizado\n\n";
	close(cliente);
	return 0;
}
