/*
 * EntidadPartida.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_ENTIDADPARTIDA_H_
#define SOURCE_MODELO_ENTIDADPARTIDA_H_

#include <string>

namespace std {

class EntidadPartida {
protected:
	int salud;
	int posX;
	int posY;
	int width;
	int length;
	string image;

public:
	EntidadPartida();
	virtual ~EntidadPartida();
	int getWidth();
	int getLength();
	void restarSalud();
};

} /* namespace std */

#endif /* SOURCE_MODELO_ENTIDADPARTIDA_H_ */
