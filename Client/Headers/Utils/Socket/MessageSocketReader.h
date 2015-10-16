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
#include "SocketQueue.h"
#include "SocketUtils.h"

using namespace std;

class MessageSocketReader: public Thread {
private:
	SocketQueue queue;
	SocketUtils* socket;
	bool isAlive;
public:
	MessageSocketReader(int sockfd);
	int run(void* data);
	virtual ~MessageSocketReader();
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGEREADER_H_ */
