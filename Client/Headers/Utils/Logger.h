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
#include <sstream>

using namespace std;

class Logger {
private:
	Logger();
	static Logger* instance;
	std::ofstream logToError;
	std::ofstream logToDebug;
	std::ofstream logToInfo;
	string getTimeStamp();
public:
	static Logger* get();
	virtual ~Logger();
	void logError(string className, string method,string message);
	void logDebug(string className, string method,string message);
	void logInfo(string className, string method,string message);
};

#endif /* SOURCE_UTILS_LOGGER_H_ */
