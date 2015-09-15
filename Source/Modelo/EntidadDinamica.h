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
		float velX = 0;
		float velY = 0;
		int framesPerSecond = 4;
		bool caminando;
		float posX;
		float posY;
		float destinoX = 0;
		float destinoY = 0;

		float distanciaA(float x, float y);
		float distanciaEnX(float x);
		float distanciaEnY(float y);

		Direccion getDireccionVertical();
		Direccion getDireccionHorizontal();
		int getLineSprite(Direccion dir);

	public:
		EntidadDinamica();
		EntidadDinamica(int vel,float posX,float posY);
		EntidadDinamica(string typeEntity, int vel,float posX,float posY, float width, float length, int fps);
		virtual ~EntidadDinamica();
		SDL_Rect getPositionOfSprite();
		string getEntityType();

		float getX();
		float getY();
		Direccion getDireccion();

		void setDestino(float x, float y);
		void trasladarse();
};

#endif /* SOURCE_MODELO_ENTIDADDINAMICA_H_ */
