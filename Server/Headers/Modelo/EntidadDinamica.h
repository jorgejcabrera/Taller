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
		float destinoX;
		float destinoY;
		int frame;
		string owner;

		float distanciaA(float x, float y);
		float distanciaEnX(float x);
		float distanciaEnY(float y);

		Direccion getDireccionVertical();
		Direccion getDireccionHorizontal();
		int getLineSprite(Direccion dir);

	public:
		void destruir();
		void setOwner(string owner);
		string getOwner();
		EntidadDinamica();
		EntidadDinamica(string nameEntity, int vel,float posX,float posY, float width, float length);
		void setInitialScreenPosition(float x,float y);
		virtual ~EntidadDinamica();
		pair<float,float>* getScreenPosition();
		pair<int,int>* getPosition();
		Direccion getDireccion();
		void setScreenPosition(float x, float y);
		void trasladarse();
		bool isWalking();
};

#endif /* SOURCE_MODELO_ENTIDADDINAMICA_H_ */
