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

#include "messageUpdate.pb.h"

using namespace std;

class Message {
private:
	messageUpdate msg;

public:
	Message();
	Message(int identifier, string typeEntity, int xPosition, int yPosition);
	virtual ~Message();
	int getLength();
	char* serializeToArray();
	string serializeAsString();
	string toString();
	//TODO borrar este metodo
	void setBody(char* body);
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGE_H_ */
