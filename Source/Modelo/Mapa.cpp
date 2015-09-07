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
			this->tiles.insert(std::make_pair(std::make_pair(j,i),*newTile));
		}
	}
}

void Mapa::show(){
	for (std::map<pair<int,int>,Tile>::iterator it = tiles.begin(); it != tiles.end();++it){
		  cout<< (*it).first.first << ";" << (*it).first.second << " => ";
		  (*it).second.show();
	}
	return;
}

Mapa::~Mapa() {
	// TODO Auto-generated destructor stub
}

