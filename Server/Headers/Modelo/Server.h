/*
 * Server.h
 *
 *  Created on: 4 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_SERVER_H_
#define SOURCE_MODELO_SERVER_H_

#define ERROR -1
#define OK 0

#include <netinet/in.h>
#include <iostream>
#include <string.h>
#include "../../Headers/Utils/Socket/Socket.h"

using namespace std;

class Server{
	private:
		int serverSocket;
		int port;
		struct sockaddr_in serverAddress;
		//bool accept_connections;

	public:
		Server(int port);
		int initSocketServer();
		//int run(void* data);
		void listenClients();
		~Server();
};

#endif /* SOURCE_MODELO_SERVER_H_ */
