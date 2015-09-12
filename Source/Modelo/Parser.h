/*
 * Parser.h
 *
 *  Created on: 4/9/2015
 *      Author: nico
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <yaml.h>

class Parser {
public:
	Parser();
	void Parsear();
	virtual ~Parser();
};

#endif /* PARSER_H_ */
