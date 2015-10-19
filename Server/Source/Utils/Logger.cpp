/*
 * Logger.cpp
 *
 *  Created on: 18 de oct. de 2015
 *      Author: jorge
 */
#include "../../Headers/Utils/Logger.h"

Logger* Logger::instance = NULL;


Logger::Logger() {
	this->logToDebug.open("log_debug.txt",ios::app);
	if(!this->logToDebug.is_open())
		cout << "[Logger] Logger: Can't open log_debug.txt"<<endl;

	this->logToError.open("log_error.txt",ios::app);
	if(!this->logToDebug.is_open())
		cout << "[Logger] Logger: Can't open log_error.txt"<<endl;
}

Logger* Logger::get(){
	if(!instance){
		instance = new Logger();
	}
	return instance;
}

void Logger::logDebug(string className, string method,string message){
	time_t     now = time(0);
	struct tm  tstruct;
	char       time[80];
	tstruct = *localtime(&now);
	strftime(time, sizeof(time), "%m-%d-%X", &tstruct);

	logToDebug <<"[" << time <<"] "<<"["<<className<<"]"<<" "<<"["<<method<<"]"<<" :"<<message << std::endl;
}

void Logger::logError(string className, string method,string message){
	time_t     now = time(0);
	struct tm  tstruct;
	char       time[80];
	tstruct = *localtime(&now);
	strftime(time, sizeof(time), "%m-%d-%X", &tstruct);

	logToError << "[" << time <<"] "<<"["<<className<<"]"<<" "<<"["<<method<<"]"<<" :"<<message << std::endl;
}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}
