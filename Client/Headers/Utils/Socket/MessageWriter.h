/*
 * MessageWriter.h
 *
 *  Created on: 11 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_UTILS_SOCKET_MESSAGEWRITER_H_
#define SOURCE_UTILS_SOCKET_MESSAGEWRITER_H_

#include "../Thread.h"

using namespace std;

class MessageWriter: public Thread {
public:
	MessageWriter();
	int run(void* data);
	virtual ~MessageWriter();
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGEWRITER_H_ */
