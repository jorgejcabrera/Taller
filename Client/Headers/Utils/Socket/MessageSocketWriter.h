/*
 * MessageWriter.h
 *
 *  Created on: 11 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_UTILS_SOCKET_MESSAGESOCKETWRITER_H_
#define SOURCE_UTILS_SOCKET_MESSAGESOCKETWRITER_H_
#define ERROR -1
#define OK 0
#include "../Thread.h"
#include "SocketQueue.h"
#include "SocketUtils.h"

using namespace std;

class MessageSocketWriter: public Thread {
private:
	SocketQueue queue;
	SocketUtils* socket;
public:
	MessageSocketWriter(int sockfd);
	/*
	*Saca los mensajes de la cola, los serializa, y los envia por el socket
	*/
	int run(void* data);
	/*
	*Ponemos los mensajes en la cola de novedades
	*/
	void sendMessage(Message msg);
	virtual ~MessageSocketWriter();
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGEWRITER_H_ */
