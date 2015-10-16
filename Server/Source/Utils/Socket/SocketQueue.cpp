/*
 * SocketQueue.cpp
 *
 *  Created on: 8 de oct. de 2015
 *      Author: jorge
 */

#include "../../../Headers/Utils/Socket/SocketQueue.h"

SocketQueue::SocketQueue() {
	this->lock = SDL_CreateMutex();
}

void SocketQueue::queuing(Message msg){
	/*
	 *If the mutex is already locked by another thread, then SDL_LockMutex
	 *will not return until the thread that locked it unlocks it
	 **/
	this->lockQueue();
	this->queue.push(msg);
	this->unlockQueue();
}

Message SocketQueue::pullTail(){
	this->lockQueue();
	Message message = this->pullTailWithoutLock();
	this->unlockQueue();
	return message;

}

Message SocketQueue::pullTailWithoutLock(){
	Message message = this->queue.front();
	this->queue.pop();
	return message;

}

void SocketQueue::lockQueue(){
	SDL_LockMutex(lock);
}

void SocketQueue::unlockQueue(){
	SDL_UnlockMutex(lock);
}

bool SocketQueue::isEmpty(){
	return this->queue.size() <= 0;
}
int SocketQueue::getSize(){
	return this->queue.size();
}

SocketQueue::~SocketQueue() {
	SDL_DestroyMutex(this->lock);
}
