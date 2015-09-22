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
	void destruir();
	int getWidth();
	int getLength();
	string getPathImage();
	void setPosition(int x,int y);
	void setPathImage(string path);
	pair<int,int>* getPosition();
	void drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY);
	void restarSalud();
};

} /* namespace std */

#endif /* SOURCE_MODELO_ENTIDADPARTIDA_H_ */
