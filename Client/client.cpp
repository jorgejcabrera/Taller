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
  int puerto = 7891;
  int bufsize = 10;
  char buffer[bufsize];
  bool salir = false;

  struct sockaddr_in serverAddr;

  if((cliente = socket(PF_INET,SOCK_STREAM,0))<0){
    cout << "Error al crear el socket cliente"<<endl;
    exit(0);
  }

  cout << "Escriba # para acabar la comunicacion"<<endl;
  cout << "\t\t\t[s] para empezar"<<endl;
  cin>>a;

  cout<<"Socket creado"<<endl;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(puerto);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if(connect(cliente,(struct sockaddr *)&serverAddr,sizeof(serverAddr))==0)
    cout<<"Conexion con el servidor "<<inet_ntoa(serverAddr.sin_addr)<<endl;

  cout<<"Esperando confirmacion del servidor"<<endl;
  read(cliente,buffer,bufsize);

  cout<<"Respuesta recibida: "<<buffer;
  cout<<"\nRecuerde poner el asterisco al final para mandar un mensaje *\nEscriba # para terminar la conexion"<<endl;

  do{
    cout<<"Escribir un mensaje: ";
    do{
      cin>>buffer;
      write(cliente,buffer,bufsize+1);
      if(*buffer == '#'){
        write(cliente,buffer,bufsize+1);
        *buffer = '*';
        salir = true;
      }
    }while(*buffer != 42);

    cout<<"Mensaje recibido: ";
    do{
      read(cliente,buffer,bufsize);
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
