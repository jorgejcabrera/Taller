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

#include "../Utils/Socket/SocketUtils.h"
#include "../Utils/Socket/MessageSocketWriter.h"
#include "../Utils/Socket/MessageSocketReader.h"
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

class Client {
private:
	MessageSocketWriter* writeThread;
	MessageSocketReader* readThread;
	SocketUtils* socketUtils;
	int port;
	int sockfd;
	int status;
	string ip;
	string name;
	void readReceivedMessage(Message msg);
public:
	Client(string ip, int port);
	int connectToServer();
	int getStatus();
	void sendMessage(Message msg);
	void communicateWithServer();
	virtual ~Client();
};

#endif /* SOURCE_MODELO_CLIENT_H_ */
