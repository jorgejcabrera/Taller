/*
 * Server.h
 *
 *  Created on: 4 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_SERVER_H_
#define SOURCE_MODELO_SERVER_H_

#define ERROR 0
#define OK 1

#include "GameSettings.h"
#include "DefaultSettings.h"
#include "EntidadPartida.h"
#include "../Utils/Socket/SocketUtils.h"
#include "../Utils/Socket/SocketQueue.h"
#include "../Utils/Socket/Message.h"
#include "../../Headers/Control/GameController.h"
#include "../Utils/Thread.h"
#include "Client.h"
#include <netinet/in.h>
#include <iostream>
#include <string.h>
#include <ctime>
#include <list>
#include <map>

using namespace std;

class Server : public Thread{
private:
	SocketQueue* readQueue;
	map<string,Client*> clients;
	GameController* gController;
	GameSettings* gameSettings;
	bool isAlive;
	bool gameRunning;
	int serverSocket;
	int port;
	struct sockaddr_in serverAddress;
	int clientsQty;
	/*
	* ALGUIEN PUEDE COMENTAR PARA QUE ES ESTA LISTA DE ENTIDADES?
	* */
	list<int> idEntitiesUpdated;
	/*
	* ?
	* */
	time_t lastReportedServer;
	/*
	* Verifican el tipo del msg, y en caso de poder aplicar los cambios indicados en el cuerpo del msg devuelve true
	* */
	bool checkForPingMsg(Message* msg);
	bool checkForExitMsg(Message* msg);
	bool checkForAttackMsg(Message* msg);
	bool checkForCreateMsg(Message* msg);
	bool checkForUpdMsg(Message* msg);
	bool checkForBuildingMsg(Message* msg);
	/*
	* Envían msg a los clientes activos, sobre las novedades de las entidades de la partida
	* */
	void sendDinamicEntitesChanges();
	void sendNewEntities();
	void sendNewsResources();
	void sendFallenEntites();
	void sendNewStaticEntites();

public:
	Server(int port, GameController *myController, int qtyUsers);
	int initSocketServer();
	/*
	* escuchamos nuevas conexiones de clientes, y le mandamos toda la conf de la partida
	* */
	int run(void * data);
	/* 
	* lee los mensajes de la cola y actualiza el modelo
 	* */
 	void processReceivedMessages();
	/*
	* ?
	* */
	void notifyClients();
	/*
	* inicia la conexion con el cliente, pide el usuario y se fija si es nuevo o si tiene que 
	* levantar data de antes porque se reconecto
	* */
	bool initConnection(Client *newClient);
	/*
	* ?
	* */
	void pingMessage();
	/*
	* ?
	* */
	void verifyClientsConections();
	/*
	* setea los nuevos tiles vistos y envia 1 msje al correspondiente cliente por cada nuevo tile
	* */ 
	void setSeenTiles();
	/*
	* ?
	* */
	void sendSeenTiles(string client);
	/*
	* Controla la cantidad de clientes conectados, si supero el limite establecido devuelve false, sino true
	* */
	bool acceptingNewClients();
	/*
	* Notifica a los clientes cuando arranca el juego, es decir... cuando deberian empezar a dibujar el escenario
	* */
	void notifyGameInitToClients();
	/*
	* Verifico si estoy esperando clientes, si estoy esperando meto un delay
	* */
	void verifyWaitingClients();

	/*
	* Cuando se conecta un nuevo cliente, creo todas sus entidades, centro civico y aldeanos
	* */
	void createEntitiesForClient(Client* newClient);

	list<Client*> getActiveClients();
	list<Message*> getProtagonistasMessages();
	bool isRunning();
	void shutDown();
	void sendColours(Client* client);
	~Server();
};

#endif /* SOURCE_MODELO_SERVER_H_ */
