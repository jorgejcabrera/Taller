/*
 * Message.h
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_UTILS_SOCKET_MESSAGE_H_
#define SOURCE_UTILS_SOCKET_MESSAGE_H_

#include <string>

using namespace std;

class Message {

private:
	int sizeBody=1024;
	string body;

public:
	Message(string msg);
	virtual ~Message();
	string getBody();
	char * getBodyToWrite();
	int getBodySize();
	void setBody(char* bodyReceived);
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGE_H_ */
