/*
 * MessageReader.h
 *
 *  Created on: 11 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_UTILS_SOCKET_MESSAGEREADER_H_
#define SOURCE_UTILS_SOCKET_MESSAGEREADER_H_

#include "../Thread.h"

using namespace std;

class MessageReader: public Thread {
public:
	MessageReader();
	int run(void* data);
	virtual ~MessageReader();
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGEREADER_H_ */
