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
	for(int i = 0; i < DefaultSettings::getMapHeight(); i++){
		//barrido horizontal del mapa
		for(int j = 0; j < DefaultSettings::getMapWidth(); j++){
			Tile* newTile =  new Tile(j,i);
			this->tiles.insert(std::make_pair(std::make_pair(j,i),*newTile));
		}
	}
}

Tile* Mapa::getTileAt(int x,int y){
	return &(this->tiles.at(make_pair(x,y)));
}

map<pair<int,int>,Tile>* Mapa::getTiles(){
	return &this->tiles;
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

