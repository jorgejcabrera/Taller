/*
 * Resource.cpp
 *
 *  Created on: Oct 17, 2015
 *      Author: juan
 */

#include "../../Headers/Modelo/Resource.h"

using namespace std;

Resource::Resource(string tipo,int x,int y) {
	this->position.first = x;
	this->position.second = y;
	this->width = 1;
	this->length = 1;
	this->name = tipo;
	//Aca estaban los path de los recursos, hay que crear vistaResource en el cliente y ponerlos ahi
}

//Saco este metodo para usar el name de la clase entidad Partida para que funcione el envio de novedades a los clientes
/*string Resource::getTipo(){
	return this->tipo;
}*/

Resource::~Resource() {
	// TODO Auto-generated destructor stub
}

