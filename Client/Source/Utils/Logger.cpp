/*
 * Logger.cpp
 *
 *  Created on: 18 de oct. de 2015
 *      Author: jorge
 */
#include "../../Headers/Utils/Logger.h"

Logger* Logger::instance = NULL;


Logger::Logger(string path) {
	this->logger.open(path.c_str(),ios::app);
	if(!this->logger.is_open())
		cout << "[Logger] Logger: Can't open "<< path.c_str()<<endl;
}

Logger* Logger::get(){
	if(!instance){
		instance = new Logger("LogDelAge.txt");
	}
	return instance;
}

void Logger::log(string className, string method,string message){
	logger << "["<<className<<"]"<<" "<<"["<<method<<"]"<<" :"<<message << std::endl;
}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}
