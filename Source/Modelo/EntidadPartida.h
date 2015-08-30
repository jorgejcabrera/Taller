/*
 * EntidadPartida.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_ENTIDADPARTIDA_H_
#define SOURCE_MODELO_ENTIDADPARTIDA_H_

namespace std {

class EntidadPartida {
private:
	int salud;
	int cordX;
	int cordY;

public:
	EntidadPartida();
	virtual ~EntidadPartida();
	void restarSalud();
};

} /* namespace std */

#endif /* SOURCE_MODELO_ENTIDADPARTIDA_H_ */
