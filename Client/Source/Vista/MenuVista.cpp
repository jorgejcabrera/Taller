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
	this->pathImage = "../../Taller/Images/Menu/Menu3.jpg";
	this->pathPergamino = "../../Taller/Images/Menu/pergamino.jpg";
	this->bigHeight = GameSettings::GetInstance()->getAlturaMenuInferior();
	this->littleStripSise = 10;
	this->mediumStripSise = 20;
	this->miniMapHeight = 0;
	this->drawDescription = false;
	//this->posXvertexFirstButton = GameSettings::GetInstance()->getScreenWidth()/2 ;
	this->posXvertexFirstButton = 50;
	this->posYvertexFirstButton = GameSettings::GetInstance()->getScreenHeight() - bigHeight;
	this->sideFirstButton = 50;
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
	else if (this->drawEntities) this->drawEntitiesSelected();

	if (strings["name"] == "Barracks") {
		string path = GameSettings::GetInstance()->imagePathPersonajesByType("aldeanoSolo");
		PicassoHelper::GetInstance()->renderObject(path,this->posXvertexFirstButton, this->posYvertexFirstButton, 50, 50);
	} else if (strings["name"] == "Castle") {
		string path = GameSettings::GetInstance()->imagePathPersonajesByType("soldadoSolo");
		PicassoHelper::GetInstance()->renderObject(path,this->posXvertexFirstButton, this->posYvertexFirstButton, 50, 50);
		string pathCobra = GameSettings::GetInstance()->imagePathPersonajesByType("cobraSolo");
		PicassoHelper::GetInstance()->renderObject(pathCobra,this->posXvertexFirstButton*2, this->posYvertexFirstButton, 50, 50);
		string pathHorse = GameSettings::GetInstance()->imagePathPersonajesByType("caballoSolo");
		PicassoHelper::GetInstance()->renderObject(pathHorse,this->posXvertexFirstButton*3, this->posYvertexFirstButton, 50, 50);
	}else if (strings["name"] == "aldeano"){
		string pathCastle = GameSettings::GetInstance()->getEntityConfig("Castle")->getPath();
		PicassoHelper::GetInstance()->renderObject(pathCastle,this->posXvertexFirstButton, this->posYvertexFirstButton, 50, 50);
		string pathArmy = GameSettings::GetInstance()->getEntityConfig("Army")->getPath();
		PicassoHelper::GetInstance()->renderObject(pathArmy,this->posXvertexFirstButton*2, this->posYvertexFirstButton, 50, 50);
		string pathMolino = "../../Taller/Images/Industrial_Age/MolinoSolo.png";
		PicassoHelper::GetInstance()->renderObject(pathMolino,this->posXvertexFirstButton*3, this->posYvertexFirstButton, 50, 50);
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
	this->selectedEntities.clear();
	this->drawEntities = false;
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
			found = path.find("aldeano");
			if(found!=string::npos) path=path.replace(path.find("aldeano"), sizeof("aldeano")-1, "aldeanoSolo");
			found = path.find("cobra");
			if(found!=string::npos) path=path.replace(path.find("cobra"), sizeof("cobra")-1, "cobraSolo");
			found = path.find("caballo");
			if(found!=string::npos) path=path.replace(path.find("caballo"), sizeof("caballo")-1, "caballoSolo");
			found = path.find("soldadoDesconectado");
			if(found!=string::npos) path=path.replace(path.find("soldadoDesconectado"), sizeof("soldado.")-1, "soldadoSolo");
			PicassoHelper::GetInstance()->renderObject(path,GameSettings::GetInstance()->getScreenWidth()/2, GameSettings::GetInstance()->getScreenHeight() - this->bigHeight, 100, 100);
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
	if (posMouseX > this->posXvertexFirstButton &&
			posMouseX < this->posXvertexFirstButton + this->sideFirstButton &&
			posMouseY > this->posYvertexFirstButton &&
			posMouseY < this->posYvertexFirstButton + this->sideFirstButton ) {
			result.first = atoi(strings["id"].c_str());
			//TODO Nuestro centro civico es Barracks
			if (strings["name"] == "Barracks") result.second = "aldeano";
			else if (strings["name"] == "Town Center") result.second = "aldeano";
			else if (strings["name"] == "aldeano") result.second = "Castle";
			else if (strings["name"] == "Castle") result.second = "soldado";
			else result.second = "";
	}
	if (posMouseX > this->posXvertexFirstButton*2 &&
			posMouseX < this->posXvertexFirstButton*2 + this->sideFirstButton &&
			posMouseY > this->posYvertexFirstButton &&
			posMouseY < this->posYvertexFirstButton + this->sideFirstButton ) {
			result.first = atoi(strings["id"].c_str());
			if (strings["name"] == "aldeano") result.second = "Army";
			else if (strings["name"] == "Castle") result.second = "cobra";
			else result.second = "";
	}
	if (posMouseX > this->posXvertexFirstButton*3 &&
			posMouseX < this->posXvertexFirstButton*3 + this->sideFirstButton &&
			posMouseY > this->posYvertexFirstButton &&
			posMouseY < this->posYvertexFirstButton + this->sideFirstButton ) {
			result.first = atoi(strings["id"].c_str());
			if (strings["name"] == "aldeano") result.second = "molino";
			else if (strings["name"] == "Castle") result.second = "caballo";
			else result.second = "";
	}
	return result;
}

void MenuVista::drawEntitiesSelected() {
	int cantidad;
	int width = 50;
	int posX = GameSettings::GetInstance()->getScreenWidth()/4;
	for ( map<string,int>::iterator it = this->selectedEntities.begin() ; it != this->selectedEntities.end(); ++it ) {
		string path= (*it).first;
		size_t found = path.find("Molino");
		if(found!=string::npos) path=path.replace(path.find("Molino"), sizeof("Molino")-1, "MolinoSolo");
		found = path.find("soldado.");
		if(found!=string::npos) path=path.replace(path.find("soldado."), sizeof("soldado.")-1, "soldadoSolo.");
		found = path.find("king");
		if(found!=string::npos) path=path.replace(path.find("king"), sizeof("king")-1, "kingSolo");
		found = path.find("aldeano");
		if(found!=string::npos) path=path.replace(path.find("aldeano"), sizeof("aldeano")-1, "aldeanoSolo");
		found = path.find("soldadoDesconectado");
		if(found!=string::npos) path=path.replace(path.find("soldadoDesconectado"), sizeof("soldado.")-1, "soldadoSolo");
		for ( cantidad = (*it).second ; cantidad > 0 ; --cantidad) {
			PicassoHelper::GetInstance()->renderObject(path,posX, GameSettings::GetInstance()->getScreenHeight()-110, width, 50);
			posX = posX+width;
		}
	}
}

void MenuVista::setSelectedEntities(map<string,int> entitiesToDraw) {
	this->drawEntities = true;
	this->selectedEntities = entitiesToDraw;
}

MenuVista::~MenuVista() {
}

} /* namespace std */
