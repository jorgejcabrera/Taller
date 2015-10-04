/*
 * Client.h
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_CLIENT_H_
#define SOURCE_MODELO_CLIENT_H_

#include "../Utils/Socket/Message.h"
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

class Client {
private:
	int port;
	int sockfd;
	int status;
	string ip;
	string name;
	void interpretReceivedMessage(string* msg);
public:
	Client(string ip, int port);
	int connectToServer();
	int getStatus();
	void sendMessage(string msg);
	virtual ~Client();
};

#endif /* SOURCE_MODELO_CLIENT_H_ */
