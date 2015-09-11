/*
 * EntidadDinamica.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_ENTIDADDINAMICA_H_
#define SOURCE_MODELO_ENTIDADDINAMICA_H_

#include "EntidadPartida.h"

using namespace std;

class EntidadDinamica: public EntidadPartida {
	private:

		int velocidad;
		float velX;
		float velY;

		bool caminando;

		float posX;
		float posY;
		float destinoX;
		float destinoY;

		float distanciaA(float x, float y);

		float distanciaEnX(float x);
		float distanciaEnY(float y);

	public:
		EntidadDinamica(int vel,float posX,float posY);
		virtual ~EntidadDinamica();

		// creo que no hace falta que sean publicos estos gets
		float getX();
		float getY();

		void setDestino(float x, float y);
		void trasladarse();
};

#endif /* SOURCE_MODELO_ENTIDADDINAMICA_H_ */
