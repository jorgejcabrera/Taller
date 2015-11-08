/*
 * Message.h
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_UTILS_SOCKET_MESSAGE_H_
#define SOURCE_UTILS_SOCKET_MESSAGE_H_

#include "../Logger.h"
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
	Message(string nombre);
	virtual ~Message();
	/*
	 *Devuelve el tamaño en bytes del mensaje
	 * */
	int getSize();
	/*
	 *Devuelve el tamaño del mensaje concatenado con el mensaje serializado
	 * */
	char* serializeToArray();
	string serializeAsString();
	string toString();
	/*
	* setea el id de la entidad con la que se desea interactuar
	* */
	void setTarget(int entityId);
	void setAsNewPath(bool value);
	void setOwner(string userName);
	void setContent(msg_game body);
	string getTipo();
	string getNombre();
	string getImagen();
	string getOwner();
	int getId();
	int getPositionX();
	int getPositionY();
	int getAnchoBase();
	int getAltoBase();
	int getFps();
	int getDelay();
	int getTotalFramesLine();
	int getPixelsDimension();
	int getTarget();
	void pingMessage(string nombre);
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGE_H_ */
