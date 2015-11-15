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
	bigHeight = GameSettings::GetInstance()->getAlturaMenuInferior();
	littleStripSise = 10;
	mediumStripSise = 20;
	miniMapHeight = 0;
	drawDescription = false;
	posXvertexFirstButton = GameSettings::GetInstance()->getScreenWidth()/2 ;
	posYvertexFirstButton = GameSettings::GetInstance()->getScreenHeight() - bigHeight;
	sideFirstButton = 55;
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

	if (strings["name"] == "Barracks") {
		PicassoHelper::GetInstance()->renderObject("../../Taller/Images/Personajes/soldadoSolo.png",GameSettings::GetInstance()->getScreenWidth()/2, GameSettings::GetInstance()->getScreenHeight()-GameSettings::GetInstance()->getAlturaMenuInferior(), GameSettings::GetInstance()->getAlturaMenuInferior()/2, GameSettings::GetInstance()->getAlturaMenuInferior()/2);
	} else if (strings["name"] == "Town Center") {

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
		if((*it).first!="path"){
			text = ((*it).first+":"+(*it).second);
			width = (text.size()*15 < maxWidth ) ? text.size()*15  : maxWidth;
			PicassoHelper::GetInstance()->renderText(	(GameSettings::GetInstance()->getScreenWidth()/4),
														GameSettings::GetInstance()->getScreenHeight()-this->bigHeight+offsetY,
														width,
														alturaDeLetra,
														text,
														0, 0,0);
			offsetY = offsetY+alturaDeLetra;
		}else{
			string path= (*it).second;
			size_t found = path.find("Molino");
			if(found!=string::npos) path=path.replace(path.find("Molino"), sizeof("Molino")-1, "MolinoSolo");
			found = path.find("soldado.");
			if(found!=string::npos) path=path.replace(path.find("soldado."), sizeof("soldado.")-1, "soldadoSolo.");
			found = path.find("king");
			if(found!=string::npos) path=path.replace(path.find("king"), sizeof("king")-1, "kingSolo");
			found = path.find("soldadoDesconectado");
			if(found!=string::npos) path=path.replace(path.find("soldadoDesconectado"), sizeof("soldado.")-1, "soldadoSolo");
			PicassoHelper::GetInstance()->renderObject(path,30, GameSettings::GetInstance()->getScreenHeight()-110, 100, 100);
		}
	}
	

}

void MenuVista::drawResources(map<string,int> resources){
	int posX = 10;
	int posY = 0;
	stringstream ss;
	for (map<string,int>::iterator it = resources.begin() ; it != resources.end(); ++it ) {
		ss << (*it).first <<" : " << resources[(*it).first];
		PicassoHelper::GetInstance()->renderText(posX,	posY, ss.str().size()*15, 20, ss.str(),255,255,255);
		posX = posX+ss.str().size()*15 + 30;
		ss.str("");
	}
}

pair<int, string> MenuVista::getTypeOfNewEntity(int posMouseX,int posMouseY) {
	pair<int, string> result;
	if (posMouseX > posXvertexFirstButton &&
		posMouseX < posXvertexFirstButton + sideFirstButton &&
		posMouseY > posYvertexFirstButton &&
		posMouseY < posYvertexFirstButton + sideFirstButton ) {
		result.first = atoi(strings["id"].c_str());
		//TODO revisar porque estoy diciendo que el soldado puede construir
		if (strings["name"] == "Barracks") result.second = "soldado";
		else if (strings["name"] == "Town Center") result.second = "aldeano";
		else if (strings["name"] == "soldado") result.second = "Castle";
		else result.second = "";
	}
	return result;
}

MenuVista::~MenuVista() {
}

} /* namespace std */
