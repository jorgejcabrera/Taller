/*
 * Client.h
 *
 *  Created on: 12 de oct. de 2015
 *      Author: jorlando
 */

#ifndef SOURCE_MODELO_CLIENT_H_
#define SOURCE_MODELO_CLIENT_H_

#define DISCONECTED -1
#define CONECTED 0

#include "../Utils/Socket/MessageSocketWriter.h"
#include "../Utils/Socket/MessageSocketReader.h"
#include "../Utils/Socket/Message.h"
#include "../Utils/Socket/SocketQueue.h"
#include "DefaultSettings.h"
#include <ctime>
#include <list>

class Client {
	int clientId;
	MessageSocketWriter* writeThread;
	MessageSocketReader* readThread;
	list<pair<int,int> > seenTiles;
	string userName;
	time_t lastReported;
	int status;
	pair<int, int> initialOffset;
//	colour myColour;
public:
	Client(int identifier, SocketQueue* queueUnique);
	void writeMessagesInQueue(list<Message*> messagesList);
	void writeMessagesInQueue(Message* message);
	/*
	* ?
	* */
	void startCommunication();
	/*
	* ?
	* */
	void responseUserName(string status);
	/*
	* ?
	* */
	string readUserName();
	/*
	* ?
	* */
	void reporting();
	/*
	* ?
	* */
	int getTimeSinceLastReport();
	string getUserName();
	void setUserName(string myName);
	bool isActive();
	void connect();
	int getStatus();
	/*
	* setea en la lista de tiles vistos todos los nuevos tiles vistos
	* y devuelve solo los que no habian sido vistos anteriormente
	* */
	list<pair<int,int> > setSeenTiles( list<pair<int,int> > newSeenTiles);
	list<pair<int,int> >getSeenTiles();
	list<Message*> getSeenTilesAsMessages();

	/*
	 * genero un mensaje con el offset inicial
	 */
	Message* getInitialOffsetAsMessage();
	void disconect();
	/*
	 * Configuro un offset inicial que la ventana del cliente arranque posicionada en donde estan sus entidades
	 */
	void setInitialOffset(int x, int y);
	pair<int,int> getInitialOffset();
	~Client();

};

#endif /* SOURCE_MODELO_CLIENTHANDLER_H_ */
