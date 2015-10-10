/*
 * TileVista.h
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_VISTA_TILEVISTA_H_
#define SOURCE_VISTA_TILEVISTA_H_

#include <string>
#include <iostream>

using namespace std;

class TileVista {
	pair<int,int> position;
	string pathImage;

public:
	void setPathImage(string path);
	TileVista(int x,int y);
	int getPosX();
	int getPosY();
	pair<int,int>* getPosition();
	virtual ~TileVista();
	string getPathImage();
};

#endif /* SOURCE_VISTA_TILEVISTA_H_ */
