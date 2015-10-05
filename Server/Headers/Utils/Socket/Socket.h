#ifndef SOURCE_UTILS_SOCKET_SOCKET_H_
#define SOURCE_UTILS_SOCKET_SOCKET_H_

#include <string>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include "../../../Headers/Utils/Socket/Message.h"

using namespace std;

class Socket {
	private:
		int socket;
	public:
        Socket(int socketId);
        int writeMessage(Message *msg);
        int readMessage(Message *msg);

        //TODO: ver que hacer con estos metodos.
        int recvMsg(string & msg, size_t length);
        int recvMsgSize(size_t size_length);


        int getSocket();
        void socketShutdown();
        void closeConnection();
        virtual ~Socket();
};

#endif /* SOURCE_UTILS_SOCKET_SOCKET_H_ */
