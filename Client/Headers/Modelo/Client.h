/*
 * Client.h
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_CLIENT_H_
#define SOURCE_MODELO_CLIENT_H_

#include "../Utils/Socket/Message.h"
#include <string>

using namespace std;

class Client {
private:
	int port;
	string ip;
	string name;

	/*Una vez que tengamos definido el protocolo de comunicon entre el servidor y el cliente, el cliente
	 *tendra que tener un metodo para entender ese mensaje*/
	void interpretReceivedMessage(Message* msg);
public:
	Client();
	Client(string ip, int port);
	void setName(string name);
	string getName();
	void sendMessage(Message msg);
	int connectToServer();
	void reconnectToServer();
	int getStatus();
	virtual ~Client();
};

#endif /* SOURCE_MODELO_CLIENT_H_ */
