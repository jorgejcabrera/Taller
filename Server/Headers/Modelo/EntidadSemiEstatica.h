/*
 * EntidadSemiEstatica.h
 *
 *  Created on: 22 de set. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_ENTIDADSEMIESTATICA_H_
#define SOURCE_MODELO_ENTIDADSEMIESTATICA_H_

#include "EntidadPartida.h"

namespace std {

class EntidadSemiEstatica: public EntidadPartida {
private:
	int widthPixel;
	int lengthPixel;
	int framesPerSecond;
	int frame;
	int framesInLineFile;
	/*
	*delay entre el fin de un ciclo de frames y el inicio de otro, la idea es setearlo en base al yaml
	* */
	int delay;
public:
	EntidadSemiEstatica();
	EntidadSemiEstatica(string nameEntity, int width, int length, float widthPixel, float lengthPixels,int fps);

	int getWidthPixel();
	int getLengthPixel();
	void setFramesInLineFile(int qty);
	int getFramesInLineFile();
	int getFramesPerSecond();
	void setDelay(int delayFrames);
	~EntidadSemiEstatica();
};

} /* namespace std */

#endif /* SOURCE_MODELO_ENTIDADSEMIESTATICA_H_ */
