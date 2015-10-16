/*
 * MessageReader.cpp
 *
 *  Created on: 11 de oct. de 2015
 *      Author: jorge
 */

#include "../../../Headers/Utils/Socket/MessageSocketReader.h"

MessageSocketReader::MessageSocketReader(int sockfd) {
	this->socket = new SocketUtils(sockfd);
	this->isAlive = true;
}

void MessageSocketReader::run(void *data){
	while(this->isAlive){
		cout << "Running thread client reader "<<endl;
		Message* message = this->socket->readMessage();
		cout << message->toString() << endl;
		//TODO interpretar mensaje
		if (!message)
			shutdown(this->socket->getSocket(),0);
	}
}

MessageSocketReader::~MessageSocketReader() {
	// TODO Auto-generated destructor stub
}
