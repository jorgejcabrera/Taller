/*
 * SequenceUtils.cpp
 *
 *  Created on: 15 de oct. de 2015
 *      Author: jorlando
 */

#include "../../Headers/Utils/SequenceUtils.h"

SequenceUtils* SequenceUtils::instance = NULL;

SequenceUtils::SequenceUtils(){
	//arranco la secuencia en 100 para que no tenga el mismo numero que los clientes, no se si eso puede llegar a afectar en algo
	this->id = 100;
}

SequenceUtils* SequenceUtils::GetInstance() {
	if (!instance) {
		instance = new SequenceUtils();
	}
	return instance;
}

int SequenceUtils::getSequence(){
	this->id++;
	return this->id;
}

SequenceUtils::~SequenceUtils(){
	this->id = 0;
}
