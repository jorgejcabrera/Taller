/*
 * EntidadDinamica.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_ENTIDADDINAMICA_H_
#define SOURCE_MODELO_ENTIDADDINAMICA_H_

#include "EntidadPartida.h"
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
		float velX;
		float velY;
		bool caminando;
		pair<int,int> position;
		float destinoX;
		float destinoY;
		float distanciaA(float x, float y);
		float distanciaEnX(float x);
		float distanciaEnY(float y);
		Direccion getDireccionVertical();
		Direccion getDireccionHorizontal();

	public:
		EntidadDinamica();
		EntidadDinamica(int vel,int posX,int posY);
		pair<int,int>* getPosition();
		Direccion getDireccion();
		void setPosition(int x,int y);
		void setScreenPosition(float x, float y);
		void trasladarse();
		virtual ~EntidadDinamica();
};

#endif /* SOURCE_MODELO_ENTIDADDINAMICA_H_ */
