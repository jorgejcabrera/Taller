/*
 * Message.h
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_UTILS_SOCKET_MESSAGE_H_
#define SOURCE_UTILS_SOCKET_MESSAGE_H_

#include <string.h>
#include <sstream>
#include <iostream>
#include <arpa/inet.h>
#include <stdint.h>

using namespace std;

class Message {
public:
	Message();
	virtual ~Message();
	string getSerializeAsString();
	virtual string toString();
	int getLength();
	void setBody(char* bodyReceived);
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGE_H_ */
