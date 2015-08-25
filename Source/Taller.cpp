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
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				active = 0; /* End */
		}
	}

	/* Clear screen */
	SDL_FillRect(demo_screen, NULL,SDL_MapRGBA(demo_screen->format, 0, 0, 255, 255));

	/* Exit */
	SDL_Quit();
	return 0;
}
