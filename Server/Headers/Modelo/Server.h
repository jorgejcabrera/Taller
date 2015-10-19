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
#include "../Utils/Socket/SocketUtils.h"
#include "../Utils/Socket/SocketQueue.h"
#include "../Utils/Socket/Message.h"
#include "../Utils/Thread.h"
#include "Client.h"
#include <map>
#include "GameSettings.h"
#include "EntidadPartida.h"
#include "../../Headers/Control/GameController.h"
#include "../../Headers/Utils/Socket/MessageSocketReader.h"

using namespace std;

class Server : public Thread{
	private:
		SocketQueue* readQueue;
		int serverSocket;
		int port;
		struct sockaddr_in serverAddress;
		map<int,Client*> clients;
		GameController *gController;
		MessageSocketReader* readThread;
		list<int> idEntitiesUpdated;

	public:
		Server(int port, GameController *myController);
		int initSocketServer();
		//int run(void* data);
		int run(void * data);
		void processReceivedMessages();
		void notifyClients();
		~Server();
};

#endif /* SOURCE_MODELO_SERVER_H_ */
