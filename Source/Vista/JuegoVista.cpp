/*
 * JuegoVista.cpp
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#include "JuegoVista.h"

void JuegoVista::drawIsometricMap(const string &file){
	int posX = 0;
	int posY = 0;
	for (map<pair<int,int>,Tile*>::iterator it = this->juego->getMap()->getTiles()->begin(); it != this->juego->getMap()->getTiles()->end();++it){
		Tile* tileActual = (*it).second;
		//transformo coordenadas cartesianas a isométricas
		posY = (tileActual->getPosX()+tileActual->getPosY()) * DefaultSettings::getTileSize() / 2;
		posX = (tileActual->getPosX()-tileActual->getPosY()) * DefaultSettings::getTileSize() + DefaultSettings::getScreenWidth() / 2;	//comienzo a dibujar de la mitad de la pantalla
		picassoHelper->renderObject(file,posX,posY,  DefaultSettings::getTileSize() * 2, DefaultSettings::getTileSize());
	}
}

void JuegoVista::actualizarMapa(){
	const int VELOCIDAD_SCROLL_UNO = 1 * 40;
		const int VELOCIDAD_SCROLL_DOS = 3 * 40;
		const int ANCHO_BORDE = 50;

		// borde derecho
		int BORDE_DERECHO_UNO_SCROLL = DefaultSettings::getScreenWidth() - ANCHO_BORDE * 2;
		int BORDE_DERECHO_DOS_SCROLL = DefaultSettings::getScreenWidth() - ANCHO_BORDE;

		// borde izquierdo
		int BORDE_IZQUIERDO_UNO_SCROLL = 40;
		int BORDE_IZQUIERDO_DOS_SCROLL = 20;

		// borde superior
		const int BORDE_SUPERIOR_UNO = 40;
		const int BORDE_SUPERIOR_DOS = 20;
		// limites
			const int LIMITE_DERECHO = -320; // limite de la posicion x inicio de la imagen
			const int LIMITE_IZQUIERDO = 20;

		int posicionX = 0;
			int posicionY = 0;
			int posX_inicioMapa = DefaultSettings::getScreenWidth() / 2;
			int posicionMapaY = 0;
		// obtiene la posicion del mouse

			//picassoHelper->actualizarVista();
				SDL_GetMouseState(&posicionX, &posicionY);

				cout << "posicion del mouse: (" << posicionX << ", " << posicionX << ") " << endl;

				if (posicionX >= BORDE_DERECHO_UNO_SCROLL
								&& posicionX <= BORDE_DERECHO_DOS_SCROLL
								&& !((posX_inicioMapa <= LIMITE_DERECHO))) {
							posX_inicioMapa -= 1 * VELOCIDAD_SCROLL_UNO;
							cout << "### posicion del mouse: (" << posicionX << ", " << posicionX << ") " << endl;
						}

						if (posicionX >= BORDE_DERECHO_DOS_SCROLL
								&& !((posX_inicioMapa <= LIMITE_DERECHO))) {
							posX_inicioMapa -= 1 * VELOCIDAD_SCROLL_DOS;
						}

						if ((posicionX >= BORDE_IZQUIERDO_DOS_SCROLL)
								&& (posicionX <= BORDE_IZQUIERDO_UNO_SCROLL)
								&& !((posX_inicioMapa >= LIMITE_IZQUIERDO))) {
							posX_inicioMapa += 1 * VELOCIDAD_SCROLL_UNO;
						}

						if (posicionX <= BORDE_IZQUIERDO_DOS_SCROLL
								&& !((posX_inicioMapa >= LIMITE_IZQUIERDO))) {
							posX_inicioMapa += 1 * VELOCIDAD_SCROLL_DOS;
						}

	int tilePosX = 0;
	int tilePosY = 2;
	string imagePath = "../Taller_tp/Images/grass_new.png"; // de prueba
		for (map<pair<int,int>,Tile>::iterator it = this->juego->getMap()->getTiles()->begin(); it != this->juego->getMap()->getTiles()->end();++it){
			Tile* tileActual = &((*it).second);
			//transformo coordenadas cartesianas a isométricas
			tilePosY = (tileActual->getPosX()+tileActual->getPosY()) * DefaultSettings::getTileSize() / 2;
			tilePosX = (tileActual->getPosX()-tileActual->getPosY()) * DefaultSettings::getTileSize() + posX_inicioMapa;
			picassoHelper->renderObject(imagePath,tilePosX,tilePosY,  DefaultSettings::getTileSize() * 2, DefaultSettings::getTileSize());
		}

			//busca eventos
					SDL_PollEvent(event);

}

void JuegoVista::drawEntities(){
	pair<int,int> isometricPosition;
	for(map<pair<int,int>,EntidadPartida*>::iterator it=this->juego->getMap()->getEntities()->begin();it!=this->juego->getMap()->getEntities()->end();++it){
		EntidadPartida* entidad = (*it).second;
		isometricPosition = picassoHelper->getIsometricPosition(entidad);
		picassoHelper->renderObject(entidad->getPathImage(), isometricPosition.first , isometricPosition.second,entidad->getWidth() * 2 * DefaultSettings::getTileSize(), (entidad->getLength()-1) * DefaultSettings::getTileSize() * 2);
	}
}

void JuegoVista::render(){

	picassoHelper->setFondo();

	string imagePath = "../Taller/Images/grass_new.png";
	drawIsometricMap(imagePath);
	drawEntities();
	picassoHelper->renderView();
}

void JuegoVista::renderProtagonista(){
	string imagePath = "../Taller/Images/ricardo.png";
	picassoHelper->renderObject(imagePath,20,320,50,50);
}

JuegoVista::JuegoVista(Juego* juego) {
	this->juego = juego;

	this->protagonista = new EntidadDinamica(5,20,20);

	picassoHelper = PicassoHelper::GetInstance(juego);
	picassoHelper->createContext();

}

JuegoVista::~JuegoVista() {
	picassoHelper->~PicassoHelper();
}


