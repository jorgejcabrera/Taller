/*
 * MenuVista.cpp
 *
 *  Created on: 5/10/2015
 *      Author: nico
 */

#include "../../Headers/Vista/MenuVista.h"

namespace std {

MenuVista::MenuVista() {
	// TODO Auto-generated constructor stub

}

void MenuVista::drawMe() {
	int width = GameSettings::GetInstance()->getScreenWidth()/4;
	int posY = GameSettings::GetInstance()->getScreenHeight() - this->bigHeight;
	PicassoHelper::GetInstance()->renderObject(pathImage, 0, posY, width, this->bigHeight);
	PicassoHelper::GetInstance()->renderObject(pathPergamino, width, posY, width*2, this->bigHeight);
	PicassoHelper::GetInstance()->renderObject(pathImage, width*3, posY, width, this->bigHeight);
	for (int i = 0 ; i <= GameSettings::GetInstance()->getScreenWidth() ; i = i + this->littleStripSise ) {
		PicassoHelper::GetInstance()->renderObject(pathImage, i, posY-this->littleStripSise, this->littleStripSise, this->littleStripSise);
	}
	for (int i = 0 ; i <= GameSettings::GetInstance()->getScreenWidth() ; i = i + this->littleStripSise ) {
		PicassoHelper::GetInstance()->renderObject(pathImage, i, 0, this->mediumStripSise, this->mediumStripSise);
	}
}

string MenuVista::getPath() {
//	return this->path;
}

int MenuVista::getMiniMapWidht() {
	this->miniMapWidth = GameSettings::GetInstance()->getScreenWidth()/4;
	return this->miniMapWidth;
}

int MenuVista::getMiniMapHeight() {
//	this->miniMapHeight = GameSettings::GetInstance()->getScreenHeight()- this->bigHeight;
	return this->miniMapHeight;
}

MenuVista::~MenuVista() {
}

} /* namespace std */
