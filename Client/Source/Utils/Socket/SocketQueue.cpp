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
	SDL_LockMutex(lock);
	this->queue.push(msg);
	SDL_UnlockMutex(lock);
}

Message SocketQueue::pullTail(){
	SDL_LockMutex(lock);
	Message message = this->queue.front();
	this->queue.pop();
	SDL_UnlockMutex(lock);
	return message;
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
