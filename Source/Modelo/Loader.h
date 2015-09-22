	/*
 * Loader.h
 *
 *  Created on: 12/9/2015
 *      Author: nico
 */

#ifndef LOADER_H_
#define LOADER_H_

#include <yaml.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <stdlib.h>

namespace std {

class Loader {
private:
	map<string,int>* screen;
	map<string,int>* conf;
	vector< map< string, string> >* type;
	map< string, string> * stage;
	vector< map< string, string> >* entitys;
	map< string, string> * mainCharacter;
	FILE * pFile;
	void parserError(yaml_parser_t* parser);

public:
	map< string, int> * getScreen();
	vector< map< string, string> >* getTypes();
	vector< map< string, string> >* getEntitys();
	map<string,int>* getConf();
	map< string, string> * getStage();
	map< string, string> * getMainCharacter();
	void log(string msg, string type);
	Loader();
	void load();
	virtual ~Loader();
};

} /* namespace std */

#endif /* LOADER_H_ */
