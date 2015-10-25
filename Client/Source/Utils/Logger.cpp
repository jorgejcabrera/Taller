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

	this->logToDebug.open("log_info.txt",ios::app);
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
	logToDebug <<"[" <<  getTimeStamp() <<"] "<<"["<<className<<"]"<<" "<<"["<<method<<"]"<<" :"<<message << std::endl;
}

void Logger::logError(string className, string method,string message){
	logToError << "[" <<  getTimeStamp() <<"] "<<"["<<className<<"]"<<" "<<"["<<method<<"]"<<" :"<<message << std::endl;
}

void Logger::logInfo(string className, string method, string message){
	logToInfo << "[" <<  getTimeStamp() <<"] "<<"["<<className<<"]"<<" "<<"["<<method<<"]"<<" :"<<message << std::endl;
}

string Logger::getTimeStamp(){
	time_t     now = time(0);
	struct tm  tstruct;
	char       time[80];
	tstruct = *localtime(&now);
	strftime(time, sizeof(time), "%m-%d-%X", &tstruct);
	std::string stringTime(time);
	return stringTime;
}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}
