/*
 * Client.h
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_CLIENT_H_
#define SOURCE_MODELO_CLIENT_H_

#define ERROR -1
#define OK 0

#include "../Utils/Socket/SocketUtils.h"
#include <string.h>
#include <iostream>

#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

class Client {
private:
	SocketUtils* socketUtils;
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
	bool sendMessage(char* buffer,const char* msg);
	void communicateWithServer();
	virtual ~Client();
};

#endif /* SOURCE_MODELO_CLIENT_H_ */
