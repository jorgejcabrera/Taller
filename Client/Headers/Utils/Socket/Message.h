/*
 * Message.h
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_UTILS_SOCKET_MESSAGE_H_
#define SOURCE_UTILS_SOCKET_MESSAGE_H_

#include <string>
#include <arpa/inet.h>

using namespace std;

class Message {

private:
	int length;
	string body;

public:
	Message(string msg);
	virtual ~Message();
	string toString();
	char * getBodyToWrite();
	int getBodySize();
	void setBody(char* bodyReceived);
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGE_H_ */
