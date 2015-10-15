/*
 * MessageSocketWritter.cpp
 *
 *  Created on: 13 de oct. de 2015
 *      Author: jorlando
 */

#include "../../../Headers/Utils/Socket/MessageSocketWriter.h"

MessageSocketWriter::MessageSocketWriter(int sockfd) {
	this->socket = new SocketUtils(sockfd);
	this->isAlive = true;
}

void MessageSocketWriter::writeMessage(Message msg){
	this->queue.queuing(msg);
}

int MessageSocketWriter::run(void* data){
	while(this->isAlive){
		while(!this->queue.isEmpty()){
			Message msg = ((MessageSocketWriter*)data)->queue.pullTail();
			if( this->socket->writeMessage(&msg) < 0){
				cout << "ERROR: No se puedieron enviar mensajes al servidor"<< endl;
				return ERROR;
			 }
		}
	}
	return OK;
}

MessageSocketWriter::~MessageSocketWriter() {
	// TODO Auto-generated destructor stub
}

void MessageSocketWriter::stopWrite(){
	this->isAlive = false;
}
