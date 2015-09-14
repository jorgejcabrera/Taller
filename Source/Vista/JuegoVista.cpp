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
		posY = (tileActual->getPosX()+tileActual->getPosY()) * DefaultSettings::getTileSize() / 2 + this->offSetY;
		posX = (tileActual->getPosX()-tileActual->getPosY()) * DefaultSettings::getTileSize() + DefaultSettings::getScreenWidth() / 2 + offSetX;	//comienzo a dibujar de la mitad de la pantalla
		picassoHelper->renderObject(file,posX,posY,  DefaultSettings::getTileSize() * 2, DefaultSettings::getTileSize());
	}
}

void JuegoVista::actualizarMapa(){

	 int VELOCIDAD_SCROLL_UNO = 1 * 10;
	 int VELOCIDAD_SCROLL_DOS = 3 * 10;
	 int ANCHO_BORDE = 40;

	// borde derecho
	int BORDE_DERECHO_UNO_SCROLL = DefaultSettings::getScreenWidth() - ANCHO_BORDE * 2;
	int BORDE_DERECHO_DOS_SCROLL = DefaultSettings::getScreenWidth() - ANCHO_BORDE;

	// borde izquierdo
	int BORDE_IZQUIERDO_UNO_SCROLL = ANCHO_BORDE *2;
	int BORDE_IZQUIERDO_DOS_SCROLL = ANCHO_BORDE;

	// borde superior
	int BORDE_SUPERIOR_UNO = ANCHO_BORDE * 2;
	int BORDE_SUPERIOR_DOS = ANCHO_BORDE;

	// limites
	int LIMITE_DERECHO = -524; // limite de la posicion x inicio de la imagen
	int LIMITE_IZQUIERDO = 524;

	int LIMITE_INFERIOR = -500;
	int LIMITE_SUPERIOR = 500;
	int posicionX = 0;
	int posicionY = 0;
	//int posicionMapaY = 0;

	SDL_GetMouseState(&posicionX, &posicionY);
	if (posicionX >= BORDE_DERECHO_UNO_SCROLL && posicionX <= BORDE_DERECHO_DOS_SCROLL && !(( (DefaultSettings::getScreenWidth() /2 + offSetX) <= LIMITE_DERECHO))) {
		offSetX -= 1 * VELOCIDAD_SCROLL_UNO;
		//cout << "### scrolllllllllll velocidad uno: (" << posicionX << ", " << posicionX << ") " << endl;
	}
	if (posicionX >= BORDE_DERECHO_DOS_SCROLL && !(( (DefaultSettings::getScreenWidth() /2 + offSetX) <= LIMITE_DERECHO))) {
		offSetX -= 1 * VELOCIDAD_SCROLL_DOS;
		//cout << "### scrolllllllllll velocidad dos: (" << posicionX << ", " << posicionX << ") " << endl;
	}

	if ((posicionX >= BORDE_IZQUIERDO_UNO_SCROLL) && (posicionX <= BORDE_IZQUIERDO_DOS_SCROLL) && !(offSetX >= LIMITE_IZQUIERDO)) {
		offSetX += 1 * VELOCIDAD_SCROLL_UNO;
	}

	if (posicionX <= BORDE_IZQUIERDO_DOS_SCROLL && !(offSetX >= LIMITE_IZQUIERDO)) {
		offSetX += 1 * VELOCIDAD_SCROLL_DOS;
	}

	/**if ((posicionY >= BORDE_SUPERIOR_DOS)
					&& (posicionY <= BORDE_SUPERIOR_UNO)
						&& !((offSetY >= LIMITE_SUPERIOR))) {
					rectanguloPasto.y += 1 * VELOCIDAD_SCROLL_UNO;
				}

				if (posicionY <= BORDE_SUPERIOR_DOS
						&& !((rectanguloPasto.y >= LIMITE_SUPERIOR))) {
					rectanguloPasto.y += 1 * VELOCIDAD_SCROLL_DOS;
				}

				if (posicionY >= BORDE_INFERIOR_UNO
						&& (posicionY <= BORDE_INFERIOR_DOS)
						&& !((rectanguloPasto.y <= LIMITE_INFERIOR))) {
					rectanguloPasto.y -= 1 * VELOCIDAD_SCROLL_UNO;
				}

				if ((posicionY >= BORDE_INFERIOR_DOS)
						&& !((rectanguloPasto.y <= LIMITE_INFERIOR))) {
					rectanguloPasto.y -= 1 * VELOCIDAD_SCROLL_DOS;
					cout << "posicion del mouse: (" << posicionX << ", "
							<< posicionX << ") " << endl;
					cout << "posicion del rectanguro: (" << rectanguloPasto.x << ", "
							<< rectanguloPasto.y << endl;
				}

				*/

drawIsometricMap("../Taller/Images/grass_new.png");

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
	string imagePath = "../Taller/Images/grass_new.png";
	actualizarMapa();
	drawIsometricMap(imagePath);
	drawEntities();
	this-> renderProtagonista();
	picassoHelper->renderView();
}

void JuegoVista::renderProtagonista(){
	string imagePath = "../Taller/Images/ricardo.png";
	picassoHelper->renderObject(imagePath,this->juego->getProtagonista()->getX(),this->juego->getProtagonista()->getY(),DefaultSettings::getTileSize(),DefaultSettings::getTileSize());
}

JuegoVista::JuegoVista(Juego* juego) {
	this->juego = juego;
	this->offSetX = 0;
	this->offSetY = 0;
	/*this->pheight = 50;
	this->pwidth = 50;
	this->offh = pheight;
	this->offw = (pwidth / 2);*/

	picassoHelper = PicassoHelper::GetInstance(juego);
	picassoHelper->createContext();

}

JuegoVista::~JuegoVista() {
	picassoHelper->~PicassoHelper();
}


