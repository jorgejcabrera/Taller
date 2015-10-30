/*
 * EntidadConfig.h
 *
 *  Created on: 17 de oct. de 2015
 *      Author: jorlando
 */

#ifndef HEADERS_MODELO_ENTIDADCONFIG_H_
#define HEADERS_MODELO_ENTIDADCONFIG_H_

#include <string>

using namespace std;

class EntidadConfig {
private:
	string name;
	string path;
	int ancho;
	int alto;
	int fps;
	int delay;
	int totalFramesLine;
	int pixelsDimension;

public:
	EntidadConfig();
	EntidadConfig(string nameNew, string pathNew, int anchoNew, int altoNew, int fpsNew, int delayNew, int totalFramesLineNew, int pixelsDimensionNew);
	virtual ~EntidadConfig();
	string getName();
	string getPath();
	int getAncho();
	int getAlto();
	int getFps();
	int getDelay();
	int getTotalFramesLine();
	int getPixelsDimension();
};

#endif /* HEADERS_MODELO_ENTIDADCONFIG_H_ */
