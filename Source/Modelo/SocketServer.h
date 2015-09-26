/*
 * SocketServer.h
 *
 *  Created on: 25 de set. de 2015
 *      Author: jorge
 */

#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>


using namespace std;

//informacion del cliente entrante
struct dataSocket{
    int descriptor;
    sockaddr_in info;
};

class SocketServer{
private:
	//variable que devuelve el so al asignar un nuevo socket
    int descriptor;
    //contiene info sobre el tipo de conecxiones que se van a realizar
    sockaddr_in info;
    bool crear_Socket();
    //ligamos el socket con so para que pueda retornar llamadas de nuestro programa
    bool ligar_kernel();
    static void* controladorCliente(void *obj);
    //este vector tiene info sobre los descriptores de los cli y comunica serv con cli
    vector<int> clientes;
public:
    SocketServer();
    void run();
    void setMensaje(const char *msn);

};

#endif // SOCKETSERVER_H
