/*
 * SequenceUtils.h
 *
 *  Created on: 15 de oct. de 2015
 *      Author: jorlando
 */

#ifndef HEADERS_UTILS_SEQUENCEUTILS_H_
#define HEADERS_UTILS_SEQUENCEUTILS_H_

#include <fstream>

using namespace std;

class SequenceUtils {
private:
	static SequenceUtils* instance;
	int id;
	SequenceUtils();

public:
	static SequenceUtils* GetInstance();
	int getSequence();
	~SequenceUtils();
};

#endif /* HEADERS_UTILS_SEQUENCEUTILS_H_ */
