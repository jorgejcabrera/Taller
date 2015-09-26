/*
 * SocketServer.cpp
 *
 *  Created on: 25 de set. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/SocketServer.h"

SocketServer::SocketServer(){
}


bool SocketServer::crear_Socket(){
	//AF_INET --> ipv4
    descriptor = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(descriptor < 0)
        return false;
    info.sin_family = AF_INET;

    //cualquier maquina que conozca nuestro ip se va a poder conectar a nuestro socket
    info.sin_addr.s_addr = INADDR_ANY;

    //convertiomos a bites
    info.sin_port = htons(4050);

    //limpiamos la estructura
    memset(&info.sin_zero,0,sizeof(info.sin_zero));
    return true;
}

bool SocketServer::ligar_kernel(){
    //ligamos el socket con el kernel
	if((bind(descriptor,(sockaddr*)&info,(socklen_t)sizeof(info))) < 0)
        return false;

	//le decimos que el servidor como maximo tendra 5 clientes
    listen(descriptor,5);
    return true;
}

void SocketServer::run(){
    if(!crear_Socket())
        throw string("Error al crear el socket");
    if(!ligar_kernel())
        throw string("Error al  ligar kernel");

    //hacemos un ciclo infinito para poder esperar a los clientes
    while (true) {
        cout << "Esperando nuevo cliente"<<endl;
        dataSocket data;
        socklen_t tam = sizeof(data.info);
        //accept --> se queda esperando hasta que llegue un cliente
        data.descriptor = accept(descriptor,(sockaddr*)&data.info,&tam);
        if(data.descriptor < 0){
            cout << "Error al acceptar al cliente"<<endl;
        }else{
            clientes.push_back(data.descriptor);
            pthread_t hilo;
            pthread_create(&hilo,0,SocketServer::controladorCliente,(void *)&data);
            pthread_detach(hilo);
        }
    }
    close(descriptor);
}

void* SocketServer::controladorCliente(void *obj){
    dataSocket *data = (dataSocket*)obj;
    while (true) {
        string mensaje;
        //este hilo esta pendiente sobre lo que nos va a decir el cliente
        while (1) {
            char buffer[10] = {0};
            //recv--> se queda esperando hasta que llegue un mensaje
            int bytes = recv(data->descriptor,buffer,10,0);
            mensaje.append(buffer,bytes);
            if(bytes < 10)
                break;
        }
        cout << mensaje << endl;
    }

    close(data->descriptor);
    pthread_exit(NULL);
}


void SocketServer::setMensaje(const char *msn){
    for(unsigned int i = 0 ; i < clientes.size() ; i++)
        cout << "bytes enviados "<< send(clientes[i],msn,strlen(msn),0);
}
