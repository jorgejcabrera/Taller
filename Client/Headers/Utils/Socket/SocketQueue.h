/*
 * SocketQueue.h
 *
 *  Created on: 8 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_UTILS_SOCKET_SOCKETQUEUE_H_
#define SOURCE_UTILS_SOCKET_SOCKETQUEUE_H_

#include <queue>
#include <string>
#include "SDL2/SDL.h"
#include "Message.h"

using namespace std;
class SocketQueue {
private:
	std::queue<std::string> queue;
	SDL_mutex* lock;
public:
	SocketQueue();

	/*si la cola esta lockeada por algun thread no podemos encolar*/
	void queuing(Message* msg);
	/*TODO al momento del sacar el mensaje de la cola lo sacamos serializado*/
	string pullTail();
	int getSize();
	virtual ~SocketQueue();
};

#endif /* SOURCE_UTILS_SOCKET_SOCKETQUEUE_H_ */