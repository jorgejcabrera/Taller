/*
 * MessageReader.h
 *
 *  Created on: 11 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_UTILS_SOCKET_MESSAGESOCKETREADER_H_
#define SOURCE_UTILS_SOCKET_MESSAGESOCKETREADER_H_

#define OK 0
#define ERROR -1

#include "../Thread.h"
#include "../Logger.h"
#include "SocketQueue.h"
#include "SocketUtils.h"
#include <list>

using namespace std;

class MessageSocketReader: public Thread {
private:
	SocketQueue* queue;
	SocketUtils* socket;
	bool isAlive;
public:
	MessageSocketReader(int sockfd);
	/*
	*leemos los mensajes del socket y los mandamos a la cola de novedades
	**/
	int run(void* data);
	/*
	*devuelve la lista de mensajes que se leyeron del socket y deben ser procesados
	**/
	list<Message*> getMessagesToProcess();
	virtual ~MessageSocketReader();

};

#endif /* SOURCE_UTILS_SOCKET_MESSAGEREADER_H_ */
