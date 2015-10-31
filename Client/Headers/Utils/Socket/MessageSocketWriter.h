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
	/*
	*cola de novedades que se van a enviar al servidor
	* */
	SocketQueue* queue;
	SocketUtils* socket;
	bool isAlive;

public:
	MessageSocketWriter(int sockfd);
	
	/*
	*sacamos los mensajes de la cola de novedades y los mandamos por el socket
	* */
	int run(void* data);
	
	/*
	*ponemos los mensajes en la cola de novedades
	* */
	void writeMessage(Message* msg);
	/*
	*borramos de la cola todos los mensajes que quedaban por escribir
	* */
	void clearQueue();
	/*
	*devuelve la cnatidad de mensajes que deben ser escritos en la cola
	* */
	int countMessage();
	void shutDown();
	virtual ~MessageSocketWriter();
	/*
	*notifica el nombre de usuario,y tiene que ser en el momento, no puede seguir el ciclo normal
	* */
	void writeMessageNow(Message *msg);
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGEWRITER_H_ */


