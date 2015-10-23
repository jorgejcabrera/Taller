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
#include "ResourceManager.h"
#include <map>
#include <list>

using namespace std ;

class Juego {
private:
	Mapa* mapa;
	map<int,EntidadDinamica*> protagonistas;
	list<EntidadDinamica*> newProtagonistas;
	ResourceManager* resourseManager;
	string currentAge;
	bool juegoFinalizado;
	GameSettings* gameSettings;
	pair<int,int> getIsometricPosition(EntidadPartida* entidad);
public:
	Juego();
	virtual ~Juego();
	//Intenta cargar la conf del yaml y setear los atributos al mapa, si por algún motivo no los encuentra setea los valores por default
	Mapa* getMap();
	void comenzarPartida();
	void terminarJuego();
	string getCurrentAge();
	void setProtagonistaAt(int velocidad,int x,int y);
	void setDestinoProtagonista(int idProtagonista, int x,int y);
	void actualizarProtagonistas();
	bool getStatusPartida();
	map<int,EntidadDinamica*> getProtagonistas();
	list<EntidadDinamica*>* getNewProtagonistasToNotify();
	pair<float,float>* getPositionOfProtagonistaById(int idBuscado);
	void cleanNewProtagonistas();

	void agregarProtagonista(string owner);
};

#endif /* SOURCE_MODELO_JUEGO_H_ */
