/*
 * Client.h
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_CLIENT_H_
#define SOURCE_MODELO_CLIENT_H_

#define ERROR -1
#define DISCONECTED -1
#define OK 0
#define CONECTED 0

#include "../Utils/Socket/MessageSocketWriter.h"
#include "../Utils/Socket/MessageSocketReader.h"
#include "../Control/GameController.h"
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "../Utils/Socket/Message.h"
#include "EntidadConfig.h"
#include "GameSettings.h"
#include "../Vista/JuegoVista.h"
#include "../Control/GameController.h"
#include "../Modelo/ResourceCounter.h"
#include <ctime>

using namespace std;

class Client {
private:
	int port;
	int sockfd;
	int status;
	string ip;
	GameController* gController;
	time_t lastReportedClient;
	time_t lastReportedServer;
	ResourceCounter* resourceCounter;
	/*
	* thread que se encarga de enviar al servidor los mensajes encolados al servidor
	* */
	MessageSocketWriter* writeThread;
	/*
	* thread que se encarga de leer los mensajes enviados por el servidor
	* */
	MessageSocketReader* readThread;

public:
	string userName;
	/*
	* instancio el servidor
	* */
	Client(GameController *gController);
	/*
	* ip al cual se va a conectar, el puerto se lo pregunto en askPortConnection()
	* intenta conectar al servidor, en caso de error devuelve -1
	* */
	int connectToServer(string ip);
	/*
	* lee la cola de novedades a procesar, y transforma las novedades en eventos
	* */
	void processReceivedMessages();
	/*
	* genera los mensajes de los eventos, y los envia al servidor
	* */
	void sendEvents();
	/*
	*
	* */
	void saveEntitiesConfig(Message* msg);
	/*
	*?
	* */
	void notifyUserName();
	/*
	*?
	* */
	void pingMessage();
	/*
	*?
	* */
	void verifyServerAlive();
	/*
	*?
	* */
	ResourceCounter* getResourceCounter();
	/*
	 * Borro todas las entidades del cliente desconectado
	 */
	void disconnectPlayer(string userName);
	bool isConected();
	/*
	* Al iniciar el cliente le pregunto a que puerto del servidor se quiere conectar
	* */
	void askPortConnection();
	/*
	 * Devuelve el userName del cliente
	 */
	string getUserName();
	virtual ~Client();
};

#endif /* SOURCE_MODELO_CLIENT_H_ */
