/*
 * Mapa.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "Mapa.h"

using namespace std;

Mapa::Mapa() {

	//barrido vertical del mapa
	for(int i = 0; i < this->defaultSettings->getMapHeight(); i++){
		//barrido horizontal del mapa
		for(int j = 0; j < this->defaultSettings->getScreenWidth(); j++){
			Tile* newTile =  new Tile(j,i);
			this->tiles.push_back(*newTile);
		}
	}
}

Mapa::~Mapa() {
	// TODO Auto-generated destructor stub
}

