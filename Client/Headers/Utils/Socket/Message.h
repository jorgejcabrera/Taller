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

private:
	int length;
	string body;
	char* serialized_message;
	void serializedMessage();

public:
	Message();
	Message(string msg);
	virtual ~Message();
	virtual string toString();
	char* getBodyToWrite();
	char* getSerializeMessage();
	int getLength();
	void setBody(char* bodyReceived);
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGE_H_ */
