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

enum stringSize {
	standarSmallSize,
	standarMediumSize,
	standardBigSize
};

class UtilsController {
private:
	UtilsController();
	static UtilsController* instance;
	GameSettings* gameSettings;

public:
	static UtilsController* GetInstance();
	pair<int,int> convertToCartesian(int xScreen,int yScreen);
	pair<int,int> getIsometricPosition(int x,int y);
	virtual ~UtilsController();
	stringSize getStringSize(EntidadPartida* entidad);
	pair<int,int> getIsometricPosition(EntidadPartida* entidad);
};

#endif /* SOURCE_CONTROL_UTILSCONTROLLER_H_ */
