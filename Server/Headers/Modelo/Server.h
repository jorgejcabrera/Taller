/*
 * Server.h
 *
 *  Created on: 4 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_SERVER_H_
#define SOURCE_MODELO_SERVER_H_

#include <netinet/in.h>
#include <iostream>
#include <string.h>
using namespace std;

class Server {
	private:
		int sockfd;
		int port;
		struct sockaddr_in remote;
		bool accept_connections;
		int createSocket();

	public:
		Server(int port);
		int prepareSocket();
		int run(void* data);
		virtual ~Server();
};

#endif /* SOURCE_MODELO_SERVER_H_ */
