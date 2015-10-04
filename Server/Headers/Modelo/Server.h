/*
 * Server.h
 *
 *  Created on: 4 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_SERVER_H_
#define SOURCE_MODELO_SERVER_H_

#include <netinet/in.h>
using namespace std;

class Server {
	private:
		int sockfd;
		int port;
		struct sockaddr_in remote;
		bool accept_connections;
		void createListeningSocket();
	public:
		Server();
		Server(int port);
		int prepareSocket();
		int run(void *data);
		void stopListening();
		virtual ~Server();
};

#endif /* SOURCE_MODELO_SERVER_H_ */
