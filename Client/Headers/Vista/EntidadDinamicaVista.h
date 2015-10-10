/*
 * EntidadDinamicaVista.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_VISTA_ENTIDADDINAMICAVISTA_H_
#define SOURCE_VISTA_ENTIDADDINAMICAVISTA_H_

#include "SDL2/SDL.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include "EntidadPartidaVista.h"

using namespace std;

enum Direccion{
	Norte,
	Noreste,
	Este,
	Sureste,
	Sur,
	Suroeste,
	Oeste,
	Noroeste,
	Sindireccion
};

class EntidadDinamicaVista: public EntidadPartidaVista {
	private:
		bool caminando;
		pair<float,float> screenPosition;
		int widthPixel;
		int lengthPixel;
		int framesPerSecond;
		float destinoX;
		float destinoY;
		int frame;
		int framesInLineFile;

		//Delay entre el fin de un ciclo de frames y el inicio de otro, la idea es setearlo en base al yaml
		int delay;
		//variable de control para indicar si estoy en medio del periodo de delay
		bool inDelayPeriod;
		// indice de segundo del delay por el cual voy
		int delayIndex;

		int getLineSprite(Direccion dir);

	public:
		void destruir();
		void setFramesInLineFile(int qty);
		int getFramesInLineFile();
		//EntidadDinamicaVista();
		EntidadDinamicaVista(int posX,int posY);
		EntidadDinamicaVista(float posX,float posY, float width, float length, int fps);
		void setInitialScreenPosition(float x,float y);
		int getWidthPixel();
		int getLengthPixel();
		virtual ~EntidadDinamicaVista();
		SDL_Rect getPositionOfSprite(int runCycles);
		int getFramesPerSecond();
		void setDelay(int delayFrames);

		pair<float,float>* getScreenPosition();
		pair<int,int>* getPosition();

		Direccion getDireccion();

		void setScreenPosition(float x, float y);
		void drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY);
};

#endif /* SOURCE_VISTA_ENTIDADDINAMICAVISTA_H_ */