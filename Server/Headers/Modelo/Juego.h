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
#include "PathFinder.h"
#include <map>
#include <list>

using namespace std ;

class Juego {
private:
	Mapa* mapa;
	map<int,EntidadDinamica*> protagonistas;
	list<EntidadDinamica*> newProtagonistas;
	ResourceManager* resourseManager;
	GameSettings* gameSettings;
	//string currentAge;
	bool juegoFinalizado;

public:
	Juego();
	/*
	*intenta cargar la conf del yaml y setear los atributos al mapa, si por algún
	*motivo no los encuentra setea los valores por default
	* */
	Mapa* getMap();
	void comenzarPartida();
	void terminarJuego();
	void setProtagonistaAt(int velocidad,int x,int y);
	void setDestinoProtagonista(int idProtagonista, int x,int y);
	bool getStatusPartida();
	map<int,EntidadDinamica*> getProtagonistas();
	list<EntidadDinamica*>* getNewProtagonistasToNotify();
	pair<int,int>* getPositionOfProtagonistaById(int idBuscado);
	void cleanNewProtagonistas();
	ResourceManager* getResourceManager();
	void agregarProtagonista(string owner);
	virtual ~Juego();
};

#endif /* SOURCE_MODELO_JUEGO_H_ */
