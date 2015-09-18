/*
 * EntidadDinamica.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_ENTIDADDINAMICA_H_
#define SOURCE_MODELO_ENTIDADDINAMICA_H_

#include "EntidadPartida.h"
#include "DefaultSettings.h"
#include "SDL2/SDL.h"
#include <math.h>
#include <iostream>
#include <fstream>

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

class EntidadDinamica: public EntidadPartida {
	private:

		int velocidad;
		bool caminando;
		pair<float,float> vecVelocity;
		pair<float,float> screenPosition;
		int widthPixel;
		int lengthPixel;
		int framesPerSecond = 20;
		float destinoX = 0;
		float destinoY = 0;
		int frame = 0;
		int framesInLineFile = 5;

		//Delay entre el fin de un ciclo de frames y el inicio de otro, la idea es setearlo en base al yaml
		int delay = 0;
		//variable de control para indicar si estoy en medio del periodo de delay
		bool inDelayPeriod = false;
		// indice de segundo del delay por el cual voy
		int delayIndex = 0;

		float distanciaA(float x, float y);
		float distanciaEnX(float x);
		float distanciaEnY(float y);

		Direccion getDireccionVertical();
		Direccion getDireccionHorizontal();
		int getLineSprite(Direccion dir);

	public:
		void setFramesInLineFile(int qty);
		int getFramesInLineFile();
		EntidadDinamica();
		EntidadDinamica(int vel,int posX,int posY);
		EntidadDinamica(string typeEntity, int vel,float posX,float posY, float width, float length, int fps);
		void setInitialScreenPosition(float x,float y);
		int getWidthPixel();
		int getLengthPixel();
		virtual ~EntidadDinamica();
		SDL_Rect getPositionOfSprite();
		string getEntityType();
		int getFramesPerSecond();
		void setDelay(int delayFrames);

		pair<float,float>* getScreenPosition();
		pair<int,int>* getPosition();

		Direccion getDireccion();

		void setScreenPosition(float x, float y);
		void trasladarse();
};

#endif /* SOURCE_MODELO_ENTIDADDINAMICA_H_ */
