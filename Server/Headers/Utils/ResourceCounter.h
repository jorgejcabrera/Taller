/*
 * ResourceCounter.h
 *
 *  Created on: 17 de nov. de 2015
 *      Author: jorge
 */

#ifndef SOURCE_UTILS_RESOURCECOUNTER_H_
#define SOURCE_UTILS_RESOURCECOUNTER_H_

#include "../Utils/Socket/Message.h"
#include <map>
#include <list>
#include <stddef.h>
#include <string>
using namespace std;

class ResourceCounter {
private:
	static ResourceCounter* instance;
	ResourceCounter();
	map<pair<string,string>, int > rscByClientAndType;
	map<pair<string,string>, int> news;

public:
	static ResourceCounter* GetInstance();
	int getRscByUserAndType(string username,string type);
	void collectResource(string username,string type,int quantity);
	list<Message*> getNews();
	virtual ~ResourceCounter();
};

#endif /* SOURCE_UTILS_RESOURCECOUNTER_H_ */
