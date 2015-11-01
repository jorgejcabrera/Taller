/*
 * LoginVista.h
 *
 *  Created on: 1 de nov. de 2015
 *      Author: jorlando
 */

#ifndef HEADERS_VISTA_LOGINVISTA_H_
#define HEADERS_VISTA_LOGINVISTA_H_

#include <string>
#include <sstream>
#include "../Modelo/PicassoHelper.h"
//#include "../Modelo/GameSettings.h"

using namespace std;

class LoginVista {

private:
	string pathImage;

public:
	LoginVista();
	virtual ~LoginVista();
	string askUserName(string initialMessage);
};


#endif /* HEADERS_VISTA_LOGINVISTA_H_ */
