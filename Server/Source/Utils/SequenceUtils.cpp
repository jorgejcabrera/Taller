/*
 * SequenceUtils.cpp
 *
 *  Created on: 15 de oct. de 2015
 *      Author: jorlando
 */

#include "../../Headers/Utils/SequenceUtils.h"

SequenceUtils* SequenceUtils::instance = NULL;

SequenceUtils::SequenceUtils(){
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
