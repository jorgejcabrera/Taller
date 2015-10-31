#ifndef SOURCE_UTILS_THREAD_H_
#define SOURCE_UTILS_THREAD_H_

#include <stdio.h>
#include <SDL2/SDL.h>
struct SDL_Thread;

using namespace std;

class Thread {
private:
	SDL_Thread *thread;
	/*
	 * This static method matches the SDL_ThreadFunction firm needed to
	 * start a thread. It just runs the virtual run method and passes
	 * the data parameter given.
	 */
	static int staticRun(void * data);

	/*
	 * Method that will be executed in this thread.
	 */
	virtual int run(void * data = NULL) = 0;

public:
	Thread();
	/*
	 * Starts the thread running the virtual run method.
	 */
	void start(void * data = NULL);
	/*
	 * Waits till the thread finishes.
	 */
	void join(int * status);
	SDL_Thread* getThread();

	virtual ~Thread();
};


#endif /* SOURCE_UTILS_THREAD_H_ */
