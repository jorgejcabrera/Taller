#ifndef SOURCE_UTILS_SOCKET_SOCKET_H_
#define SOURCE_UTILS_SOCKET_SOCKET_H_

#include <string>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sstream>
#include <netdb.h>
#include "../../../Headers/Utils/Socket/Message.h"

using namespace std;

class SocketUtils {
private:
	int socket;
public:
	SocketUtils(int socketId);
	/*
	*recibe el mensaje serializado como parametro y lo manda por el socket
	*/
	bool writeMessage(Message* message);
	/*
	*lee del buffer un mensaje y devuelve el mensaje y lo devuelve, o null en caso de error
	*/
	Message* readMessage();
	/*
	*retorna el id del socket
	*/
	int getSocket();
	virtual ~SocketUtils();
};

#endif /* SOURCE_UTILS_SOCKET_SOCKET_H_ */
