/*
 * ResourceCounter.cpp
 *
 *  Created on: 17 de nov. de 2015
 *      Author: jorge
 */

#include "../../Headers/Utils/ResourceCounter.h"

ResourceCounter* ResourceCounter::instance = NULL;

ResourceCounter::ResourceCounter() {
}

ResourceCounter* ResourceCounter::GetInstance(){
	if(!instance){
		instance = new ResourceCounter();
	}
	return instance;
}

void ResourceCounter::collectResource(string username,string type,int quantity){
	//actualizamos los recursos de cada cliente
	map<pair<string,string>, int >::iterator it = this->rscByClientAndType.find(make_pair(username,type));
	if( it != this->rscByClientAndType.end() ){
		this->rscByClientAndType.at(make_pair(username,type)) += quantity;
	}else{
		this->rscByClientAndType.insert(make_pair(make_pair(username,type),quantity));
	}
	//actualizamos la colección que mantiene las novedades
	map<pair<string,string>, int >::iterator itNews = this->news.find(make_pair(username,type));
	if( itNews != this->news.end() ){
		this->news.at(make_pair(username,type)) += quantity;
	}else{
		this->news.insert(make_pair(make_pair(username,type),this->rscByClientAndType.at(make_pair(username,type))));
	}
}

list<Message*> ResourceCounter::getNews(){
	Message* msg = NULL;
	list<Message*> newsList;
	//creamos la lista de novedades
	for(map<pair<string,string>, int>::iterator itNews = this->news.begin(); itNews!=this->news.end();++itNews){
		msg = new Message(0,"updResource");
		msg->setName(itNews->first.second);
		msg->setOwner(itNews->first.first);
		msg->setHealth(itNews->second);
		newsList.push_front(msg);
	}
	//boramos la lista de novedades
	this->news.clear();
	return newsList;
}
ResourceCounter::~ResourceCounter() {
	// TODO Auto-generated destructor stub
}

