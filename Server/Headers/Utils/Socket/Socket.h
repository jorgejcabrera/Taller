#ifndef SOURCE_UTILS_SOCKET_SOCKET_H_
#define SOURCE_UTILS_SOCKET_SOCKET_H_

#include <string>
#include <unistd.h> //close
#include <arpa/inet.h>

using namespace std;

class Socket {
	private:
		int socket;
	public:
        Socket(int sockfd);
        int socketWrite(const char * buffer, size_t length);
        //TODO: ver que hacer con estos metodos.
        int recvMsg(string & msg, size_t length);
        int recvMsgSize(size_t size_length);

        int readMessage(string & msg, size_t length);
        int getSocket();
        void socketShutdown();
        void closeConnection();
        virtual ~Socket();
};

#endif /* SOURCE_UTILS_SOCKET_SOCKET_H_ */