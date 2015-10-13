/*
 * MessageUpdate.h
 *
 *  Created on: 10 de oct. de 2015
 *      Author: jorlando
 */

#ifndef HEADERS_UTILS_SOCKET_MESSAGEUPDATE_H_
#define HEADERS_UTILS_SOCKET_MESSAGEUPDATE_H_

#include "../../../Headers/Utils/Socket/Message.h"
#include "messageUpdate.pb.h"

/*struct messageUpt {
	int id;
	string tipo;
	int x;
	int y;
};*/


class MessageUpdate: public Message {

private:
	messageUpdate msg;

public:
	MessageUpdate();
	MessageUpdate(int identifier, string typeEntity, int xPosition, int yPosition);
	virtual ~MessageUpdate();
	string toString();
};

#endif /* HEADERS_UTILS_SOCKET_MESSAGEUPDATE_H_ */





