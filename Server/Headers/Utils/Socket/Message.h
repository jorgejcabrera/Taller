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
	Message(int identifier, int xPosition, int yPosition);
	Message(int identifier,string tipoMessage, string nombreEntity, int xPosition, int yPosition, int clientConnected);
	Message(string nameEntity, string thePath, int anchoBase, int altoBase, int fps, int delay, int totalFramesLine, int pixelDimension);
	Message(string tipo, string nombreEntity, int xPosition, int yPosition, int mapaAncho, int mapaAlto);
	Message(string tipo, string nombreEntity, int xPosition, int yPosition);
	Message(string nombre);

	int getSize();
	char* serializeToArray();
	string serializeAsString();
	string toString();
	void setContent(msg_game body);
	void setHealth(int health);
	void setStrength(int strength);
	void setPrecision(float precition);

	/*
	* metodos para poder sacar la informacion del mensaje desde afuera de la clase
	* */
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
	int getHealth();
	int getStrength();
	float getPrecision();
	void setAsNewPath(bool value);
	void setOwner(string userName);
	/*
	* ?
	* */
	void pingMessage(string nombre);
	/*
	* El cliente se deconecto entonces mando la novedad con el id de la entidad desconectada
	* */
	void clientDisconect(int id);
	/*
	* ?
	* */
	void activeTile( int x, int y);
	/*
	* setea el id de la entidad con la que se desea interactuar
	* */
	void setTarget(int entityId);
	/*
	* mensaje para notificar a los clientes que el juego arranco
	* */
	void startGame();
	/*
	 * mensaje para mandar el offset inicial del cliente
	 */
	void initialOffset(int x, int y);
	/*
	 * Mensaje para mandar que un cliente perdio el juego
	 */
	void clientLost(string clientName);
	/*
	 * Mensaje para mandar que un cliente es el ganador del juego
	 */
	void clientWin(string clientName);
	void colourOfClient(string client, int colour);
	virtual ~Message();
};

#endif /* SOURCE_UTILS_SOCKET_MESSAGE_H_ */
