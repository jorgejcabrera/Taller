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

using namespace std;

enum Direccion{
	Norte,
	Noreste,
	Este,
	Sureste,
	Sur,
	Suroeste,
	Oeste,
	Noroeste,
	Sindireccion
};

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
	/*
	*Delay entre el fin de un ciclo de frames y el inicio de otro, la idea es setearlo en base al yaml
	**/
	int delay;
	/*
	*variable de control para indicar si estoy en medio del periodo de delay
	**/
	bool inDelayPeriod;
	/*
	*indice de segundo del delay por el cual voy
	**/
	int delayIndex;

	Direccion getDireccionVertical();
	Direccion getDireccionHorizontal();
	int getLineSprite(Direccion dir);

public:
	EntidadDinamicaVista();
	EntidadDinamicaVista(string myName, float width, float length, int fps);
	void destruir();
	/*
	*seteo la cantidad de frames que tiene una linea del archivo para luego poder controlar el delay
	**/
	void setFramesInLineFile(int qty);
	int getFramesInLineFile();
	int getWidthPixel();
	int getLengthPixel();
	SDL_Rect getPositionOfSprite(int runCycles);
	int getFramesPerSecond();
	void setDelay(int delayFrames);
	string toString();
	void setScreenPosition(float x,float y);
	pair<float,float> getScreenPosition();
	pair<int,int>* getPosition();
	Direccion getDireccion();
	void drawMe(pair<int,int> isometricPosition, int offSetX, int offSetY);
	string getName();
	void trasladarse();
	void walk();
	void stopWalk();
	bool isWalking();
	virtual ~EntidadDinamicaVista();

};

#endif /* SOURCE_VISTA_ENTIDADDINAMICAVISTA_H_ */
