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
#include "DefaultSettings.h"
#include "EntidadPartida.h"
#include "../../Headers/Control/GameController.h"
#include <ctime>
#include <list>

using namespace std;

class Server : public Thread{
	private:
		SocketQueue* readQueue;
		map<string,Client*> clients;
		GameController* gController;
		GameSettings* gameSettings;
		bool isAlive;
		int serverSocket;
		int port;
		struct sockaddr_in serverAddress;
		list<int> idEntitiesUpdated;
		time_t lastReportedServer;

	public:
		Server(int port, GameController *myController);
		int initSocketServer();
		/*
		*escuchamos nuevas conexiones de clientes, y le mandamos toda la conf de la partida
		* */
		int run(void * data);
		/* 
		* 1- Bajo todos los mansajes de la cola
	 	* 2- actualizo la posicion de los protagonistas
	 	* */
	 	void processReceivedMessages();
		/*
		* ?
		* */
		void notifyClients();
		/*
		*inicia la conexion con el cliente, pide el usuario y se fija si es nuevo o si tiene que 
		*levantar data de antes porque se reconecto
		* */
		void initConnection(Client *newClient);
		void pingMessage();
		/*
		*
		* */
		void verifyClientsConections();
		list<Client*> getActiveClients();
		list<Message*> getProtagonistasMessages();
		bool isRunning();
		void shutDown();
		/*
		*levanta todas entidades que tenia el cliente viejo y notifico que se volvio a conectar
		* */
		void notifyClientReconect(string userName);
		/*
		*setea los nuevos tiles vistos y envia 1 msje al correspondiente cliente por cada nuevo tile
		* */ 
		void setSeenTiles();
		void sendSeenTiles(string client);
		~Server();
};

#endif /* SOURCE_MODELO_SERVER_H_ */
