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
	this->letterHeight = this->bigHeight / 5;
	this->littleStripSise = 10;
	this->mediumStripSise = 20;
	this->miniMapHeight = 0;
	this->posXvertexFirstButton = 50;
	this->posYvertexFirstButton = GameSettings::GetInstance()->getScreenHeight() - bigHeight;
	this->sideFirstButton = 50;
	this->entitySelected = NULL;
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
	this->drawEntityDescription();
	if(this->entitySelected != NULL){
		if (this->entitySelected->getName() == "Barracks") {
			string path = GameSettings::GetInstance()->imagePathPersonajesByType("aldeanoSolo");
			PicassoHelper::GetInstance()->renderObject(path,this->posXvertexFirstButton, this->posYvertexFirstButton, 50, 50);
		} else if (this->entitySelected->getName() == "Castle") {
			string path = GameSettings::GetInstance()->imagePathPersonajesByType("soldadoSolo");
			PicassoHelper::GetInstance()->renderObject(path,this->posXvertexFirstButton, this->posYvertexFirstButton, 50, 50);
			string pathCobra = GameSettings::GetInstance()->imagePathPersonajesByType("cobraSolo");
			PicassoHelper::GetInstance()->renderObject(pathCobra,this->posXvertexFirstButton*2, this->posYvertexFirstButton, 50, 50);
			string pathHorse = GameSettings::GetInstance()->imagePathPersonajesByType("caballoSolo");
			PicassoHelper::GetInstance()->renderObject(pathHorse,this->posXvertexFirstButton*3, this->posYvertexFirstButton, 50, 50);
		}else if (this->entitySelected->getName() == "aldeano"){
			string pathCastle = GameSettings::GetInstance()->getEntityConfig("Castle")->getPath();
			PicassoHelper::GetInstance()->renderObject(pathCastle,this->posXvertexFirstButton, this->posYvertexFirstButton, 50, 50);
			string pathArmy = GameSettings::GetInstance()->getEntityConfig("Army")->getPath();
			PicassoHelper::GetInstance()->renderObject(pathArmy,this->posXvertexFirstButton*2, this->posYvertexFirstButton, 50, 50);
			string pathMolino = "../../Taller/Images/Industrial_Age/MolinoSolo.png";
			PicassoHelper::GetInstance()->renderObject(pathMolino,this->posXvertexFirstButton*3, this->posYvertexFirstButton, 50, 50);
		}
	}

}

int MenuVista::getMiniMapWidht() {
	this->miniMapWidth = GameSettings::GetInstance()->getScreenWidth()/4;
	return this->miniMapWidth;
}

int MenuVista::getMiniMapHeight() {
	return this->miniMapHeight;
}

void MenuVista::deselectedEntity() {
	//una sola entidad seleccionada
	this->entitySelected = NULL;

	//muchas entidades seleccionadas
	this->selectedEntities.clear();
}

void MenuVista::setSelectedEntity(EntidadPartidaVista* entity){
	this->entitySelected = entity;
}

void MenuVista::drawEntityDescription() {
	if (this->entitySelected != NULL){
		int offsetY = 0;
		this->renderEntityField("id", this->entitySelected->getId(), offsetY);
		offsetY = offsetY + this->letterHeight;
		this->renderEntityField("", this->entitySelected->getName(), offsetY);
		offsetY = offsetY + this->letterHeight;
		this->renderEntityField("dueno", this->entitySelected->getOwner(), offsetY);
		offsetY = offsetY + this->letterHeight;
		this->renderEntityField("salud", this->entitySelected->getHealth(), offsetY);
		offsetY = offsetY + this->letterHeight;
		this->renderEntityImage(this->entitySelected->getPathImage());
	}else{
		this->drawEntitiesSelected();
	}
}

void MenuVista::renderEntityField(string field, string value, int offset){
	stringstream ss;
	ss.str("");
	if(value != ""){
		if(field!=""){
				ss << field << ": ";
		}
		ss<< value;
		this->renderEntityText(ss.str(),offset);
	}
}

void MenuVista::renderEntityField(string field, int value, int offset){
	stringstream ss;
	ss << value;
	this->renderEntityField(field, ss.str(),offset);
}

void MenuVista::renderEntityImage(string path){
	path = DefaultSettings::covertPathOfAnimatedEntity(path);
	PicassoHelper::GetInstance()->renderObject(path,GameSettings::GetInstance()->getScreenWidth()/2, GameSettings::GetInstance()->getScreenHeight() - this->bigHeight, 100, 100);
}

void MenuVista::renderEntityText(string text, int offset){
	int maxWidth = (GameSettings::GetInstance()->getScreenWidth() - GameSettings::GetInstance()->getScreenWidth()/2);
	int width = (text.size()*15 < maxWidth ) ? text.size()*15  : maxWidth;
	PicassoHelper::GetInstance()->renderText(	(GameSettings::GetInstance()->getScreenWidth()/4),
												GameSettings::GetInstance()->getScreenHeight()-this->bigHeight+offset,
												width,
												this->letterHeight,
												text,
												0,0,0);
}

void MenuVista::drawResources(map<string,int> resources){
	int posX = 10;
	int posY = 0;
	stringstream ss;
	for (map<string,int>::iterator it = resources.begin() ; it != resources.end(); ++it ) {
		string resourceName = (*it).first;
		EntidadConfig* entity = GameSettings::GetInstance()->getEntityConfig(resourceName);
		ss << resources[resourceName];
		PicassoHelper::GetInstance()->renderObject(entity->getPath(),posX, posY, 25, 25);
		posX += 25;
		PicassoHelper::GetInstance()->renderText(posX,	posY, ss.str().size()*10, 20, ss.str(),255,255,255);
		posX += ss.str().size()*10 + 20;
		ss.str("");
	}
}

pair<int, string> MenuVista::getTypeOfNewEntity(int posMouseX,int posMouseY) {
	pair<int, string> result;
	if (this->entitySelected == NULL){
		result.second = "";
		return result;
	}
	result.first = this->entitySelected->getId();
	if (posMouseX > this->posXvertexFirstButton &&
			posMouseX < this->posXvertexFirstButton + this->sideFirstButton &&
			posMouseY > this->posYvertexFirstButton &&
			posMouseY < this->posYvertexFirstButton + this->sideFirstButton ) {
			if (this->entitySelected->getName() == "Barracks") result.second = "aldeano";
			else if (this->entitySelected->getName() == "Town Center") result.second = "aldeano";
			else if (this->entitySelected->getName() == "aldeano") result.second = "Castle";
			else if (this->entitySelected->getName() == "Castle") result.second = "soldado";
			else result.second = "";
	}
	if (posMouseX > this->posXvertexFirstButton*2 &&
			posMouseX < this->posXvertexFirstButton*2 + this->sideFirstButton &&
			posMouseY > this->posYvertexFirstButton &&
			posMouseY < this->posYvertexFirstButton + this->sideFirstButton ) {
			if (this->entitySelected->getName() == "aldeano") result.second = "Army";
			else if (this->entitySelected->getName() == "Castle") result.second = "cobra";
			else result.second = "";
	}
	if (posMouseX > this->posXvertexFirstButton*3 &&
			posMouseX < this->posXvertexFirstButton*3 + this->sideFirstButton &&
			posMouseY > this->posYvertexFirstButton &&
			posMouseY < this->posYvertexFirstButton + this->sideFirstButton ) {
			if (this->entitySelected->getName() == "aldeano") result.second = "molino";
			else if (this->entitySelected->getName() == "Castle") result.second = "caballo";
			else result.second = "";
	}
	return result;
}

void MenuVista::drawEntitiesSelected() {
	int cantidad;
	int width = 50;
	int posX = GameSettings::GetInstance()->getScreenWidth()/4;
	int posY = GameSettings::GetInstance()->getScreenHeight()-110;
	int numberOfRenderedEntities = 0;
	for ( map<string,int>::iterator it = this->selectedEntities.begin() ; it != this->selectedEntities.end(); ++it ) {
		string path = DefaultSettings::covertPathOfAnimatedEntity((*it).first);
		for ( cantidad = (*it).second ; cantidad > 0 ; --cantidad) {
			PicassoHelper::GetInstance()->renderObject(path,posX, posY, width, 50);
			posX = posX+width;
			if ( numberOfRenderedEntities == 7 ) {
				posX = GameSettings::GetInstance()->getScreenWidth()/4;
				posY = posY+53;
			}
			++numberOfRenderedEntities;
		}

	}
}

void MenuVista::setSelectedEntities(map<string,int> entitiesToDraw) {
	this->selectedEntities = entitiesToDraw;
}

MenuVista::~MenuVista() {
}

} /* namespace std */
