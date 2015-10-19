/*
 * MessageWriter.cpp
 *
 *  Created on: 11 de oct. de 2015
 *      Author: jorge
 */

#include "../../../Headers/Utils/Socket/MessageSocketWriter.h"

MessageSocketWriter::MessageSocketWriter(int sockfd) {
	this->socket = new SocketUtils(sockfd);
	this->isAlive = true;
}

void MessageSocketWriter::sendMessage(Message* msg){
	this->queue.queuing(msg);
}

int MessageSocketWriter::run(void* data){
	while(this->isAlive){
		while(!this->queue.isEmpty()){
			Message *msg = ((MessageSocketWriter*)data)->queue.pullTail();
			if( !this->socket->writeMessage(msg) < 0){
				Logger::get()->logError("MessageSocketWriter","run","Cant send message to server");
			}
		}
	}
	return OK;
}

void MessageSocketWriter::stopWrite(){
	this->isAlive = false;
}

MessageSocketWriter::~MessageSocketWriter() {
	// TODO Auto-generated destructor stub
}
