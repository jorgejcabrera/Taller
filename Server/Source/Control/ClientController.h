/*
 * ClientController.h
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_CONTROL_CLIENTCONTROLLER_H_
#define SOURCE_CONTROL_CLIENTCONTROLLER_H_

using namespace std;

class ClientController {
public:
	void addClient();
	ClientController();
	void sendAllInfoToClients();
	void sendAllInfo();
	void sendInfo();

	virtual ~ClientController();
};

#endif /* SOURCE_CONTROL_CLIENTCONTROLLER_H_ */
