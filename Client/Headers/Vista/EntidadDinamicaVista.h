/*
 * EntidadDinamicaVista.h
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_VISTA_ENTIDADDINAMICAVISTA_H_
#define SOURCE_VISTA_ENTIDADDINAMICAVISTA_H_

#include "SDL2/SDL.h"
#include <math.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "EntidadPartidaVista.h"
#include "../Modelo/Mixer.h"

using namespace std;

class EntidadDinamicaVista: public EntidadPartidaVista {
private:
	string name;
	/*
	* posicion actual en donde se encuentra el personaje
	* */
	pair<float,float> screenPosition;
	/*
	* corresponde a la posicion de pantalla donde queremos llegar
	* */
	int velocidad;
	pair<float,float> vecVelocity;
	bool caminando;
	int widthPixel;
	int lengthPixel;
	int framesPerSecond;
	float destinoX;
	float destinoY;
	int frame;
	int framesInLineFile;
	float distanciaA(float x, float y);
	float distanciaEnX(float x);
	float distanciaEnY(float y);
	list<pair<int,int> >* camino;
	/*
	* Delay entre el fin de un ciclo de frames y el inicio de otro, la idea es setearlo en base al yaml
	* */
	int delay;
	/*
	* variable de control para indicar si estoy en medio del periodo de delay
	* */
	bool inDelayPeriod;
	/*
	* indice de segundo del delay por el cual voy
	* */
	int delayIndex;
	int rangeVisibility;
	/*
	* atributo necesario para sincronizar la vista con el modelo. Si visualmete estan proximos la entidad
	* y el target, comienza la pelea.
	* */
	bool readyToAttack;
	Direccion getDireccionVertical();
	Direccion getDireccionHorizontal();
	int getLineSprite(Direccion dir);
	Direccion lastDirection;

public:
	EntidadDinamicaVista();
	EntidadDinamicaVista(string myName, float width, float length, int fps);
	/*
	* seteo la cantidad de frames que tiene una linea del archivo para luego poder controlar el delay
	* */
	void setFramesInLineFile(int qty);
	int getFramesInLineFile();
	int getWidthPixel();
	int getLengthPixel();
	int getFramesPerSecond();
	int getRangeVisibility();
	string getName();
	list<pair<int,int> >* getCamino();
	pair<float,float> getScreenPosition();
	Direccion getDireccion();
	SDL_Rect getPositionOfSprite(int runCycles);
	string toString();
	bool isReadyToAttack();
	void prepareToFight(bool value);
	void setDelay(int delayFrames);
	void setScreenPosition(float x,float y);
	void setInitialScreenPosition(float x,float y);
	void setPosition(int x,int y);
	void addTileToPath(int x,int y);
	void drawMe(pair<int,int>* offSet, int ciclos);
	void trasladarse();
	bool isWalking();
	virtual ~EntidadDinamicaVista();

};

#endif /* SOURCE_VISTA_ENTIDADDINAMICAVISTA_H_ */
