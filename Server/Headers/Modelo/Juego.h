/*
 * Juego.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_MODELO_JUEGO_H_
#define SOURCE_MODELO_JUEGO_H_

#include "Mapa.h"
#include "EntidadDinamica.h"
#include "../Modelo/DefaultSettings.h"
#include "GameSettings.h"
#include <map>

using namespace std ;

class Juego {
private:
	Mapa* mapa;
	EntidadDinamica* protagonista;
	string currentAge;
	bool juegoFinalizado;
	GameSettings* gameSettings;
	pair<int,int> offset;
	pair<int,int> getIsometricPosition(EntidadPartida* entidad);
public:
	Juego();
	virtual ~Juego();
	//Intenta cargar la conf del yaml y setear los atributos al mapa, si por algún motivo no los encuentra setea los valores por default
	Mapa* getMap();
	void actualizarOffset(int offsetX,int offsetY);
	void comenzarPartida();
	void terminarJuego();
	string getCurrentAge();
	pair<int,int>* getOffset();
	void setProtagonistaAt(int velocidad,int x,int y);
	void setDestinoProtagonista(int x,int y, int screenPositionX, int screenPositionY);
	void actualizarProtagonista();
	bool getStatusPartida();
	EntidadDinamica* getProtagonista();
};

#endif /* SOURCE_MODELO_JUEGO_H_ */
