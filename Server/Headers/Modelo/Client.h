/*
 * Client.h
 *
 *  Created on: 12 de oct. de 2015
 *      Author: jorlando
 */

#ifndef SOURCE_MODELO_CLIENT_H_
#define SOURCE_MODELO_CLIENT_H_

#include "../Utils/Socket/MessageSocketWriter.h"
#include "../Utils/Socket/Message.h"

#include <list>

class Client {
	int clientId;
	MessageSocketWriter* writeThread;

public:
	Client(int identifier);
	~Client();
	void writeMessagesInQueue(list<Message*> messagesList);
};

#endif /* SOURCE_MODELO_CLIENTHANDLER_H_ */
