/*
 * LoginVista.h
 *
 *  Created on: 21 de nov. de 2015
 *      Author: jorlando
 */
#ifndef HEADERS_VISTA_LOGINVISTA_H_
#define HEADERS_VISTA_LOGINVISTA_H_

#include <string>
#include <sstream>
#include "../Modelo/PicassoHelper.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using namespace std;

class LoginVista {
private:
	PicassoHelper* picassoHelper;
	int buttonDimension;
	int xCivic;
	int xFlag;
	int xRegicide;
	int yButtons;
	string game;
	int clientNumber;
public:
	LoginVista();
	virtual ~LoginVista();
	int askPort();
	void renderFinishLogin(string finalMessage);
	/*
	 * Pregunta el tipo de partida deseada
	 */
	string askGameType();
	/*
	 * Pregunto la cantidad de clientes
	 */
	int askClientsNumber();
	/*
	 * obtiene el resultado de hacer click en la pantalla
	 */
	bool validateSelection(int x, int y);
};


#endif /* HEADERS_VISTA_LOGINVISTA_H_ */
