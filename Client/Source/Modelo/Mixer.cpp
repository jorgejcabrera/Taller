/*
 * Mixer.cpp
 *
 *  Created on: 21 de nov. de 2015
 *      Author: nico
 */

#include "../../Headers/Modelo/Mixer.h"
Mixer* Mixer::instance = NULL;

Mixer::Mixer() {
	this->music = NULL;
	this->soundOfSword = NULL;
	this->initialize();
}

Mixer* Mixer::GetInstance() {
	if (!instance) {
		instance = new Mixer();
	}
	return instance;
}

void Mixer::initialize() {
	 //Initialize SDL
	if( SDL_Init( SDL_INIT_AUDIO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}
	 //Initialize SDL_mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
	}

	//Load music
	this->music = Mix_LoadMUS( "../Sounds/beat.wav" );
	if( this->music == NULL ) {
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
	}

	//Load sound effects
	//this->soundOfSword = Mix_LoadWAV( "../Sounds/scratch.wav" );
	this->soundOfSword = Mix_LoadWAV( "../Sounds/campana.wav" );
	if( this->soundOfSword == NULL ) {
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
	}

	this->soundOfNosEstanAtacando = Mix_LoadWAV( "../Sounds/nos_estan_atacando_empire_earth.wav" );
	if( this->soundOfNosEstanAtacando == NULL ) {
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
	}

	this->soundOfCarAttack = Mix_LoadWAV( "../Sounds/car_attack.wav" );
	if( this->soundOfCarAttack == NULL ) {
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
	}
	this->soundOfCarStart = Mix_LoadWAV( "../Sounds/car_start.wav" );
	if( this->soundOfCarStart == NULL ) {
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
	}

	this->soundOfHorse = Mix_LoadWAV( "../Sounds/horse.wav" );
	if( this->soundOfHorse == NULL ) {
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
	}
}

void Mixer::playMusic() {
	Mix_PlayMusic( this->music, -1 );
}

void Mixer::playEffect() {
	Mix_PlayChannel( -1, this->soundOfSword, 0 );
}

void Mixer::playNosEstanAtacando() {
	Mix_PlayChannel( -1, this->soundOfNosEstanAtacando, 0 );
}

void Mixer::playCarAttack() {
	Mix_PlayChannel( -1, this->soundOfSword, 0 );
}

void Mixer::playCarStart() {
	Mix_PlayChannel( -1, this->soundOfCarStart, 0 );
}

void Mixer::playHorse() {
	Mix_PlayChannel( -1, this->soundOfHorse, 0 );
}

void Mixer::startOrStopMusic() {
	if( Mix_PausedMusic() == 1 ) Mix_ResumeMusic();
	else Mix_PauseMusic();
}

Mixer::~Mixer() {
	//Free the sound effects
	Mix_FreeChunk(this->soundOfSword);
	this->soundOfSword = NULL;
	//Free the music
	Mix_FreeMusic(this->music);
	this->music = NULL;
	//Quit SDL subsystems
	Mix_Quit();
}
