//============================================================================
// Name        : Taller.cpp
// Author      : Jorge
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "SDL/SDL.h"

using namespace std;

SDL_Surface *demo_screen;
float demo_time_measure = 0.0f;
float demo_time_step = 0.0f;
/* Convert from timespec to float */

float demo_convert_time(struct timespec *ts){
	float accu;
	/* Combine the value into floating number */
	accu = (float)ts->tv_sec; /* Seconds that have gone by */
	accu *= 1000000000.0f; /* One second is 1000x1000x1000 nanoseconds, s -> ms, us, ns */
	accu += (float)ts->tv_nsec; /* Nanoseconds that have gone by */
	/* Bring it back into the millisecond range but keep the nanosecond resolution */
	accu /= 1000000.0f;
	return accu;
}

/* Start time */
void demo_start_time(){
	struct timespec ts;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
	demo_time_measure = demo_convert_time(&ts);
}

/* End time */
void demo_end_time(){
	struct timespec ts;
	float delta;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
	delta = demo_convert_time(&ts)-demo_time_measure; /* Find the distance in time */
	demo_time_step = delta/(1000.0f/16.0f); /* Weird formula, equals 1.0f at 16 frames a second */
}

int main( int argc, char* args[] ) {

	SDL_Event ev;
	int active;

	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());

	/* Open main window */
	demo_screen = SDL_SetVideoMode(640, 480, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (!demo_screen)
		fprintf(stderr, "Could not set video mode: %s\n", SDL_GetError());

	/* Main loop */
	active = 1;
	while (active) {
		/* Handle events */
		while(SDL_PollEvent(&ev))
		{
			if(ev.type == SDL_QUIT)
				active = 0; /* End */
		}
		/* Start time */
		demo_start_time();
		/* Clear screen */
		SDL_FillRect(demo_screen,NULL,SDL_MapRGBA(demo_screen->format,0,0,255,255));
		/* Show screen */
		SDL_Flip(demo_screen);
		/* End time */
		demo_end_time();
	}

	/* Clear screen */
	SDL_FillRect(demo_screen, NULL,SDL_MapRGBA(demo_screen->format, 0, 0, 255, 255));

	/* Exit */
	SDL_Quit();
	return 0;
}
