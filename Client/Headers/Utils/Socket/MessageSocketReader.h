/*
 * MessageReader.h
 *
 *  Created on: 11 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_UTILS_SOCKET_MESSAGESOCKETREADER_H_
#define SOURCE_UTILS_SOCKET_MESSAGESOCKETREADER_H_

#include "../Thread.h"
#include "SocketQueue.h"
#include "SocketUtils.h"

using namespace std;

class MessageSocketReader: public Thread {
private:
	SocketQueue queue;
	SocketUtils* socket;
public:
	MessageSocketReader();
	int run(void* data);
	virtual ~MessageSocketReader();
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGEREADER_H_ */
