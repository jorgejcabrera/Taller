#ifndef SOURCE_UTILS_SOCKET_SOCKET_H_
#define SOURCE_UTILS_SOCKET_SOCKET_H_

#include <string>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include "../../../Headers/Utils/Socket/Message.h"

using namespace std;

class SocketUtils {
private:
	int socket;
public:
        SocketUtils(int socketId);
        void setSocket(int socket);
        /*
        *recibe el mensaje serializado como parametro y lo manda por el socket
        */
        bool writeMessage(char* message,int size);
        /*
        *lee del buffer la cantidad de bytes pasada como parametros y devuelve el
        *mensaje, o null en caso de error
        */
        Message* readMessage(char* buffer,int size);

        //TODO: ver que hacer con estos metodos.
        int recvMsg(string & msg, size_t length);
        int recvMsgSize(size_t size_length);


        int getSocket();
        void socketShutdown();
        void closeConnection();
        virtual ~SocketUtils();
};

#endif /* SOURCE_UTILS_SOCKET_SOCKET_H_ */
