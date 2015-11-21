/*
 * Mixer.h
 *
 *  Created on: 21 de nov. de 2015
 *      Author: nico
 */

#ifndef HEADERS_MODELO_MIXER_H_
#define HEADERS_MODELO_MIXER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include <string>

class Mixer {
private:
	//The music that will be played
	Mix_Music *music;
	//The sound effects that will be used
	Mix_Chunk *soundOfSword;
public:
Mixer();
void initialize();
void playMusic();
void playEffect();
void startOrStopMusic();
virtual ~Mixer();


};

#endif /* HEADERS_MODELO_MIXER_H_ */
