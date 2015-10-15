/*
 * MessageWriter.cpp
 *
 *  Created on: 11 de oct. de 2015
 *      Author: jorge
 */

#include "../../../Headers/Utils/Socket/MessageSocketWriter.h"

MessageSocketWriter::MessageSocketWriter(int sockfd) {
	this->socket = new SocketUtils(sockfd);
}

void MessageSocketWriter::sendMessage(Message msg){
	this->queue.queuing(msg);
}

int MessageSocketWriter::run(void* data){
	while(!this->queue.isEmpty()){
		Message msg = ((MessageSocketWriter*)data)->queue.pullTail();
		if( this->socket->writeMessage(msg.serializeToArray(),msg.getSize()) < 0){
			cout << "ERROR: No se puedieron enviar mensajes al servidor"<< endl;
			return ERROR;
		}
	}
	return OK;
}

MessageSocketWriter::~MessageSocketWriter() {
	// TODO Auto-generated destructor stub
}
