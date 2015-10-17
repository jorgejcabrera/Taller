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

#include "messageGame.pb.h"

using namespace std;

class Message {
private:
	msg_game msg;

public:
	Message();
	Message(int identifier, int xPosition, int yPosition);
	Message(int identifier,string tipoMessage, string nombreEntity, int xPosition, int yPosition);
	Message(string nameEntity, string thePath, int anchoBase, int altoBase, int fps, int delay, int totalFramesLine, int pixelDimension);
	Message(string tipo, string nombreEntity, int xPosition, int yPosition);

	virtual ~Message();
	int getSize();
	char* serializeToArray();
	string serializeAsString();
	string toString();
	void setContent(msg_game body);

	//Defino metodos para poder sacar la informacion del mensaje desde afuera de la clase
	int getId();
	int getPositionX();
	int getPositionY();
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGE_H_ */
