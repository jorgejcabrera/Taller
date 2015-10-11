/*
 * MessageUpdate.h
 *
 *  Created on: 10 de oct. de 2015
 *      Author: jorlando
 */

#ifndef HEADERS_UTILS_SOCKET_MESSAGEUPDATE_H_
#define HEADERS_UTILS_SOCKET_MESSAGEUPDATE_H_

#include "../../../Headers/Utils/Socket/Message.h"

struct messageUpt {
	string id;
	string tipo;
	int x;
	int y;
};


class MessageUpdate: public Message {

private:
	messageUpt msg;

public:
	MessageUpdate();
	MessageUpdate(string identifier, string typeEntity, int xPosition, int yPosition);
	virtual ~MessageUpdate();
	string toString();
};

#endif /* HEADERS_UTILS_SOCKET_MESSAGEUPDATE_H_ */





