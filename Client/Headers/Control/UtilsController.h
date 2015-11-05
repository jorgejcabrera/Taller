/*
 * UtilsController.h
 *
 *  Created on: 17 de set. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_CONTROL_UTILSCONTROLLER_H_
#define SOURCE_CONTROL_UTILSCONTROLLER_H_
#include <iostream>
#include "../Modelo/GameSettings.h"

using namespace std;

class UtilsController {
private:
	UtilsController();
	static UtilsController* instance;
	GameSettings* gameSettings;

public:
	static UtilsController* GetInstance();
	/*
	 *transforma de coordenadas de pantalla a coordenadas cartesianas
	 * */
	pair<int,int> convertToCartesian(int xScreen,int yScreen);
	/*
	 *encuentra la posición de pantalla en donde se debería deibujar una entidad que esta
	 *en las coordenadas cartesianas (x,y). Luego la centra con los tiles, y retorna la posicion.
	 * */
	pair<int,int> getIsometricPosition(EntidadPartidaVista* entidad);
	/*
	 *devuelve la posición isométrica correspondiente a la posición cartesiana pasada como parámetro
	 * */
	pair<int,int> getIsometricPosition(int x,int y);
	virtual ~UtilsController();
};

#endif /* SOURCE_CONTROL_UTILSCONTROLLER_H_ */
