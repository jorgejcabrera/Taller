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
	pair<int,int> position;
	int width;
	int length;
	string pathImage;

public:
	EntidadPartida();
	virtual ~EntidadPartida();
	int getWidth();
	int getLength();
	string getPathImage();
	void push(int x, int y);
	pair<int,int>* getPosition();
	void restarSalud();
};

} /* namespace std */

#endif /* SOURCE_MODELO_ENTIDADPARTIDA_H_ */
