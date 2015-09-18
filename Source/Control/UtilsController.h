/*
 * UtilsController.h
 *
 *  Created on: 17 de set. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_CONTROL_UTILSCONTROLLER_H_
#define SOURCE_CONTROL_UTILSCONTROLLER_H_
#include <iostream>
#include "../Modelo/DefaultSettings.h"

using namespace std;

class UtilsController {
private:
	UtilsController();
	static UtilsController* instance;

public:
	static UtilsController* GetInstance();
	pair<int,int> convertToCartesian(int xScreen,int yScreen);
	pair<int,int> getIsometricPosition(int x,int y);
	virtual ~UtilsController();
};

#endif /* SOURCE_CONTROL_UTILSCONTROLLER_H_ */