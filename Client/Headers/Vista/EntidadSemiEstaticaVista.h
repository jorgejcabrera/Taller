/*
 * EntidadSemiEstaticaVista.h
 *
 *  Created on: 22 de set. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_VISTA_ENTIDADSEMIESTATICAVISTA_H_
#define SOURCE_VISTA_ENTIDADSEMIESTATICAVISTA_H_

#include "SDL2/SDL.h"
#include "EntidadPartidaVista.h"

namespace std {

class EntidadSemiEstaticaVista: public EntidadPartidaVista {
private:
	int widthPixel;
	int lengthPixel;
	int framesPerSecond;
	float destinoY;
	int frame;
	int framesInLineFile;

	//Delay entre el fin de un ciclo de frames y el inicio de otro, la idea es setearlo en base al yaml
	int delay;
	//variable de control para indicar si estoy en medio del periodo de delay
	bool inDelayPeriod;
	// indice de segundo del delay por el cual voy
	int delayIndex;
public:
	EntidadSemiEstaticaVista();
	EntidadSemiEstaticaVista(int width, int length,float widthPixel,float lengthPixels, int fps);

	int getWidthPixel();
	int getLengthPixel();
	void setFramesInLineFile(int qty);
	int getFramesInLineFile();
	int getFramesPerSecond();
	void setDelay(int delayFrames);
	SDL_Rect getPositionOfSprite(int ciclos);
	void drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY, int ciclos);

	virtual ~EntidadSemiEstaticaVista();
};

} /* namespace std */

#endif /* SOURCE_VISTA_ENTIDADSEMIESTATICAVISTA_H_ */
