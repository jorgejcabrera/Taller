/*
 * JuegoVista.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "JuegoVista.h"

	void JuegoVista::drawIsometricMap(){
	int posX = 0;
	int posY = 0;
	for (map<pair<int,int>,Tile*>::iterator it = this->juego->getMap()->getTiles()->begin(); it != this->juego->getMap()->getTiles()->end();++it){
		Tile* tileActual = (*it).second;
		//transformo coordenadas cartesianas a isométricas
		posY = (tileActual->getPosX()+tileActual->getPosY()) * DefaultSettings::getTileSize() / 2 + this->offSetY;
		posX = (tileActual->getPosX()-tileActual->getPosY()) * DefaultSettings::getTileSize() + DefaultSettings::getScreenWidth() / 2 + offSetX;	//comienzo a dibujar de la mitad de la pantalla
		picassoHelper->renderObject(tileActual->getPathImage(),posX,posY,  DefaultSettings::getTileSize() * 2, DefaultSettings::getTileSize());
	}
}

	void JuegoVista::actualizarMapa() {

		int posicionX = 0;
		int posicionY = 0;

		SDL_GetMouseState(&posicionX, &posicionY);

		if (posicionX >= DefaultSettings::getMargenDerechoUno()
				&& posicionX < DefaultSettings::getMargenDerechoDos()
				&& !(offSetX < DefaultSettings::getLimiteDerecho())) {
			offSetX -= DefaultSettings::getVelocidadScrollUno();
		}

		if (posicionX >= DefaultSettings::getMargenDerechoDos()
				&& !(offSetX < DefaultSettings::getLimiteDerecho())) {
			offSetX -= 1 * DefaultSettings::getVelocidadScrollDos();
		}

		if ((posicionX >= DefaultSettings::getMargenIzquierdoUno())
				&& (posicionX < DefaultSettings::getMargenIzquierdoDos())
				&& !(offSetX > DefaultSettings::getLimiteIzquierdo())) {
			offSetX += DefaultSettings::getVelocidadScrollUno();
		}

		if (posicionX <= DefaultSettings::getMargenIzquierdoDos()
				&& !(offSetX > DefaultSettings::getLimiteIzquierdo())) {
			offSetX += DefaultSettings::getVelocidadScrollDos();
		}

		if ((posicionY <= DefaultSettings::getMargenSuperiorUno())
				&& (posicionY > DefaultSettings::getMargenSuperiorDos())
				&& !((offSetY > DefaultSettings::getLimiteSuperior()))) {
			offSetY += DefaultSettings::getVelocidadScrollUno();
		}

		if (posicionY <= DefaultSettings::getMargenSuperiorDos()
				&& !((offSetY > DefaultSettings::getLimiteSuperior()))) {
			offSetY += DefaultSettings::getVelocidadScrollDos();
		}

		if (posicionY >= DefaultSettings::getMargenInferiorUno()
				&& (posicionY < DefaultSettings::getMargenInferiorDos())
				&& !((offSetY < DefaultSettings::getLimiteInferior()))) {
			offSetY -= DefaultSettings::getVelocidadScrollUno();
		}

		if ((posicionY >= DefaultSettings::getMargenInferiorDos())
				&& !((offSetY < DefaultSettings::getLimiteInferior()))) {
			offSetY -= DefaultSettings::getVelocidadScrollDos();
		}

		this->drawIsometricMap();

	}

void JuegoVista::drawEntities(){
	pair<int,int> isometricPosition;
	for(map<pair<int,int>,EntidadPartida*>::iterator it=this->juego->getMap()->getEntities()->begin();it!=this->juego->getMap()->getEntities()->end();++it){
		EntidadPartida* entidad = (*it).second;
		isometricPosition = picassoHelper->getIsometricPosition(entidad);
		picassoHelper->renderObject(entidad->getPathImage(), (isometricPosition.first+ this->offSetX) , (isometricPosition.second+ this->offSetY) ,entidad->getWidth() * 2 * DefaultSettings::getTileSize(), (entidad->getLength()-1) * DefaultSettings::getTileSize() * 2);
	}
}

void JuegoVista::render(){

	picassoHelper->clearView();
	//actualizarMapa();
	this->drawIsometricMap();
	drawEntities();
	this->renderProtagonista();
	this->picassoHelper->renderView();
}

void JuegoVista::renderProtagonista(){
	if(!protagonistaSeMovio){
		pair<int,int> isometricPosition = picassoHelper->getIsometricPosition(this->juego->getProtagonista());
		picassoHelper->renderObject(this->juego->getProtagonista()->getPathImage(), isometricPosition.first + DefaultSettings::getTileSize()/2, isometricPosition.second - 25, DefaultSettings::getTileSize(), DefaultSettings::getTileSize(), this->juego->getProtagonista()->getPositionOfSprite());
	}else{
		pair<float,float>* screenPosition = juego->getProtagonista()->getScreenPosition();
		picassoHelper->renderObject(this->juego->getProtagonista()->getPathImage(), screenPosition->first - DefaultSettings::getTileSize()/2, screenPosition->second - juego->getProtagonista()->getLengthPixel() / 2 , DefaultSettings::getTileSize(), DefaultSettings::getTileSize(), this->juego->getProtagonista()->getPositionOfSprite());
	}
}

void JuegoVista::protagonistaYaSeMovio(){
	this->protagonistaSeMovio = true;
}

JuegoVista::JuegoVista(Juego* juego) {
	this->juego = juego;
	this->offSetX = 0;
	this->offSetY = 0;
	this->protagonistaSeMovio = false;
	picassoHelper = PicassoHelper::GetInstance(juego);
	picassoHelper->createContext();
}

JuegoVista::~JuegoVista() {
	picassoHelper->~PicassoHelper();
}


