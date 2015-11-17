/*
 * ResourceCounter.cpp
 *
 *  Created on: 17 de nov. de 2015
 *      Author: jorge
 */

#include "../../Headers/Utils/ResourceCounter.h"

ResourceCounter* ResourceCounter::instance = NULL;

ResourceCounter::ResourceCounter() {
	// TODO Auto-generated constructor stub

}

ResourceCounter* ResourceCounter::GetInstance(){
	if(!instance){
		instance = new ResourceCounter();
	}
	return instance;
}

void ResourceCounter::collectResource(string username,string type,int quantity){
	map<pair<string,string>, int >::iterator it = this->rscByClientAndType.find(make_pair(username,type));
	if( it != this->rscByClientAndType.end() ){
		this->rscByClientAndType.at(make_pair(username,type)) += quantity;
	}else{
		this->rscByClientAndType.insert(make_pair(make_pair(username,type),quantity));
	}
}
ResourceCounter::~ResourceCounter() {
	// TODO Auto-generated destructor stub
}

