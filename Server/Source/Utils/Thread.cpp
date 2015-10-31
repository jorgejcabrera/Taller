#include "../../Headers/Utils/Thread.h"

#include <SDL2/SDL_thread.h>

struct ThreadAndParam{
	Thread * t;
	void * param;
};


Thread::Thread() {
	thread = NULL;
}

void Thread::start(void * data){
	struct ThreadAndParam *tap = new struct ThreadAndParam();
	tap->t = this;
	tap->param = data;
	thread = SDL_CreateThread(staticRun, NULL/*Threads name*/, tap);

	// deleting this cause some randoms segmentation faults!!!
	//delete tap;
}

void Thread::join(int * status){
	SDL_WaitThread(thread , status);
}

int Thread::staticRun(void * data){
	struct ThreadAndParam *tap = (ThreadAndParam *) data;
	return tap->t->run(tap->param);
}

SDL_Thread* Thread::getThread(){
	return this->thread;
}

Thread::~Thread() {
	//Its not necessary to destroy the thread. SDL_WaitThread is the dtor.
}
