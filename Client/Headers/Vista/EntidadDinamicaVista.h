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
#include <sstream>
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
		string name;
		bool caminando;
		/*
		*posicion actual en donde se encuentra el personaje
		**/
		pair<float,float> currentScreenPosition;
		/*
		*corresponde a la proxima posicion de pantalla a dibujarse
		**/
		pair<float,float> nextScreenPosition;
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
		EntidadDinamicaVista();
		EntidadDinamicaVista(string myName, float width, float length, int fps);
		void destruir();
		void setFramesInLineFile(int qty);
		int getFramesInLineFile();
		void setInitialScreenPosition(float x,float y);
		int getWidthPixel();
		int getLengthPixel();
		SDL_Rect getPositionOfSprite(int runCycles);
		int getFramesPerSecond();
		void setDelay(int delayFrames);
		string toString();
		void setScreenPosition(pair<float,float> screenPosition);
		pair<float,float>* getScreenPosition();
		void setNextScreenPosition(pair<float,float> nextScreenPosition);
		pair<float,float>* getNextScreenPosition();
		/*
		*setea la proxima posicion de pantalla como la actual
		**/
		void updateScreenPosition();
		pair<int,int>* getPosition();
		Direccion getDireccion();
		void drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY);
		string getName();
		virtual ~EntidadDinamicaVista();

};

#endif /* SOURCE_VISTA_ENTIDADDINAMICAVISTA_H_ */
