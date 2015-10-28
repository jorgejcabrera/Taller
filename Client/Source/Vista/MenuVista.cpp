/*
 * MenuVista.cpp
 *
 *  Created on: 5/10/2015
 *      Author: nico
 */

#include "../../Headers/Vista/MenuVista.h"

namespace std {

MenuVista::MenuVista() {
	//TODO modificar esto para obtenerse del default o del yaml
	pathImage = "../../Taller/Images/Menu/Menu3.jpg";
	pathPergamino = "../../Taller/Images/Menu/pergamino.jpg";
	bigHeight = 120;
	littleStripSise = 10;
	mediumStripSise = 20;
	miniMapHeight = 0;
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
	if (this->drawDescription) this->drawEntityDescription();
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

void MenuVista::deselectedEntity() {
	this->strings.clear();
	this->drawDescription = false;
}

void MenuVista::setSelectedEntityDescription(map<string,string> description) {
	this->strings = description;
	this->drawDescription = true;
}

void MenuVista::drawEntityDescription() {
	int offsetY = 0;
	int alturaDeLetra = this->bigHeight/strings.size();
	string text;
	int maxWidth = (GameSettings::GetInstance()->getScreenWidth() - GameSettings::GetInstance()->getScreenWidth()/2);
	int width;
	for (map<string,string>::iterator it = strings.begin() ; it != strings.end() ; it++) {
		text = ((*it).first+":"+(*it).second);
		width = (text.size()*15 < maxWidth ) ? text.size()*15  : maxWidth;
		PicassoHelper::GetInstance()->renderText(	(GameSettings::GetInstance()->getScreenWidth()/4),
													GameSettings::GetInstance()->getScreenHeight()-this->bigHeight+offsetY,
													width,
													alturaDeLetra,
													text,
													0, 0,0);
		offsetY = offsetY+alturaDeLetra;
	}

}

MenuVista::~MenuVista() {
}

} /* namespace std */
