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
		stringstream ss;
		while(!this->queue.isEmpty()){
			ss.str("");
			ss << "Queue size "<< this->queue.getSize();
			Logger::get()->logDebug("MessageSocketWriter","run",ss.str());
			Message msg = ((MessageSocketWriter*)data)->queue.pullTail();
			if(!this->socket->writeMessage(&msg)){
			 	Logger::get()->logError("MessageSocketWriter","run","Cant find message to socket");
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
