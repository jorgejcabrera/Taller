/*
 * Logger.h
 *
 *  Created on: 18 de oct. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_UTILS_LOGGER_H_
#define SOURCE_UTILS_LOGGER_H_

#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

class Logger {
private:
	Logger(string path);
	static Logger* instance;
	std::ofstream logger;
public:
	static Logger* get();
	virtual ~Logger();
	void log(string className, string method,string message);
};

#endif /* SOURCE_UTILS_LOGGER_H_ */
