/*
 * Client.h
 *
 *  Created on: 12 de oct. de 2015
 *      Author: jorlando
 */

#ifndef SOURCE_MODELO_CLIENT_H_
#define SOURCE_MODELO_CLIENT_H_

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
	string userName;
	time_t lastReported;

public:
	Client(int identifier, SocketQueue *queueUnique);
	~Client();
	void writeMessagesInQueue(list<Message*> messagesList);
	void writeMessagesInQueue(Message* message);
	void startCommunication();
	string readUserName();
	string getUserName();
	void setUserName(string myName);
	void responseUserName(string status);
	void reporting();
	bool isActive();
};

#endif /* SOURCE_MODELO_CLIENTHANDLER_H_ */
