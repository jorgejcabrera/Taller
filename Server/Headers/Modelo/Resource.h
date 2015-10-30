/*
 * Resource.h
 *
 *  Created on: Oct 17, 2015
 *      Author: juan
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include "EntidadEstatica.h"

class Resource: public EntidadEstatica {
//private:
	//No uso el tipo, uso el name de entidadPArtida porque se usa para notificar a los clientes y la logica ya esta adaptada
	//string tipo;
public:
	Resource(string tipo,int x,int y);
	//string getTipo();
	virtual ~Resource();
};

#endif /* RESOURCE_H_ */
