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
#include <stdio.h>
#include <stdlib.h>


#include "messageGame.pb.h"

using namespace std;

class Message {
private:
	msg_game msg;

public:
	Message();
	Message(int identifier, string typeEntity, int xPosition, int yPosition);
	virtual ~Message();
	/*
	 *Develve el tamaño en bytes del mensaje
	 * */
	int getSize();
	/*
	 *Devuelve el tamaño del mensaje concatenado con el mensaje serializado
	 * */
	char* serializeToArray();
	string serializeAsString();
	string toString();
	//TODO borrar este metodo
	void setContent(msg_game body);

	//Defino metodos para poder sacar la informacion del mensaje desde afuera de la clase
	string getTipo();
	int getId();
	int getPositionX();
	int getPositionY();
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGE_H_ */
