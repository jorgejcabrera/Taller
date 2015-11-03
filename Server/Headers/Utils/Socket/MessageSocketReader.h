/*
 * MessageSocketReader.h
 *
 *  Created on: 13 de oct. de 2015
 *      Author: jorlando
 */

#ifndef SOURCE_UTILS_SOCKET_MESSAGESOCKETREADER_H_
#define SOURCE_UTILS_SOCKET_MESSAGESOCKETREADER_H_
#define ERROR -1
#define OK 0
#include "../Thread.h"
#include "SocketQueue.h"
#include "SocketUtils.h"
#include "Message.h"
#include <list>

using namespace std;

class MessageSocketReader: public Thread {
private:
	SocketQueue* queue;
	SocketUtils* socket;
	bool isAlive;

public:
	MessageSocketReader(int sockfd, SocketQueue *queueUnique);
	int run(void* data);
	void shutDown();
	void restart();
	list<Message*> getMessagePendingProcess();
	/*
	*metodo utilizado para leer mensajes on line, la idea es utilizarlo solo para leer el user name
	* */
	Message* readMessageNow();
	virtual ~MessageSocketReader();
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGEREADER_H_ */
