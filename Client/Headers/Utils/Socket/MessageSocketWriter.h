/*
 * MessageSocketWriter.h
 *
 *  Created on: 13 de oct. de 2015
 *      Author: jorlando
 */


#ifndef SOURCE_UTILS_SOCKET_MESSAGESOCKETWRITER_H_
#define SOURCE_UTILS_SOCKET_MESSAGESOCKETWRITER_H_
#define ERROR -1
#define OK 0
#include "../Thread.h"
#include "SocketQueue.h"
#include "SocketUtils.h"
#include "Message.h"

using namespace std;

class MessageSocketWriter: public Thread {
private:
	SocketQueue* queue;
	SocketUtils* socket;
	bool isAlive;

public:
	MessageSocketWriter(int sockfd);
	/*
	*Sacamos los mensajes de la cola de novedades y los mandamos por el socket
	*/
	int run(void* data);
	/*
	*Ponemos los mensajes en la cola de novedades
	*/
	void writeMessage(Message* msg);
	void stopWrite();
	virtual ~MessageSocketWriter();
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGEWRITER_H_ */


