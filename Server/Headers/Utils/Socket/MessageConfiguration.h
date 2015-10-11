/*
 * MessageConfiguration.h
 *
 *  Created on: 10 de oct. de 2015
 *      Author: jorlando
 */

#ifndef HEADERS_UTILS_SOCKET_MESSAGECONFIGURATION_H_
#define HEADERS_UTILS_SOCKET_MESSAGECONFIGURATION_H_

#include "../../../Headers/Utils/Socket/Message.h"

using namespace std;

struct messageConfig {
	string nombre;
	string imagen;
	int ancho_base;
	int alto_base;
	int fps;
	int delay;
	int total_frames_line;
	int pixels_dimension;
};


class MessageConfiguration: public Message {

private:
	messageConfig msg;

public:
	MessageConfiguration();
	MessageConfiguration(string name, string path, int width, int heigth);
	MessageConfiguration(string name, string path, int width, int heigth, int fpsParam, int delayParam, int totalFramesLine, int pixelConfig);
	void setFPS(int fpsToSet);
	void setDelay(int delayToSet);
	void setTotalFramesLine(int totalFramesInLine);
	void setPixel(int pixelToSet);
	virtual ~MessageConfiguration();
	string toString();
};

#endif /* HEADERS_UTILS_SOCKET_MESSAGECONFIGURATION_H_ */
