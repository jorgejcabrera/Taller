/*
 * Loader.cpp
 *
 *  Created on: 12/9/2015
 *      Author: nico
 */

#include "../../Headers/Modelo/Loader.h"

namespace std {
Loader::Loader() {
	 pFile = fopen ("logAge.log","w");
}

void Loader::load() {
	FILE *fh = fopen("../firstMap.yml", "r");
	yaml_parser_t parser;
	yaml_event_t  event;
	map< string, string> stringMap;
	string map,key,scalarValue,value;
	vector<pair<string,string> > nestedStructures;
	pair<string,string> structure;

	try{
		pFile = fopen ("logAge.log","w");
		/* Initialize parser */
			if(!yaml_parser_initialize(&parser)) log("Failed to initialize parser", "WARNING");
			if(fh == NULL) log("Failed to open file", "ERROR");
			else {
				yaml_parser_set_input_file(&parser, fh);


				/* START new code */
				do {
					if (!yaml_parser_parse(&parser, &event)) {
						log("ERROR PARSING - Loading Default Settings","WARNING");
						//parserError(&parser);
						goto Cleanup;
					}
					switch(event.type)
					{
					case YAML_NO_EVENT:{
						log("No event!","INFO"); break;
					}
					/* Stream start/end */
					case YAML_STREAM_START_EVENT:{
						log("STREAM START","INFO"); break;
					}
					case YAML_STREAM_END_EVENT:{
						log("STREAM END","INFO");   break;
					}
					/* Block delimeters */
					case YAML_DOCUMENT_START_EVENT:{
						log("Start Document","INFO"); break;
					}
					case YAML_DOCUMENT_END_EVENT:{
						log("End Document","INFO");   break;
					}
					case YAML_SEQUENCE_START_EVENT:
					{
						nestedStructures.push_back(pair<string,string>(key,"sequence"));
						key="";
						log("Start Sequence","INFO");
						break;
					}
					case YAML_SEQUENCE_END_EVENT:
					{
						nestedStructures.pop_back();
						log("End Sequence","INFO");
						break;
					}

					case YAML_MAPPING_START_EVENT:
					{
						log("Start Mapping","INFO");
						nestedStructures.push_back(pair<string,string>(key,"map"));
						key="";
						break;
					}

					case YAML_MAPPING_END_EVENT:
			    	{
			    		structure = nestedStructures.at(nestedStructures.size()-1);
						nestedStructures.pop_back();
						if (structure ==pair<string,string>("","map")){
							try{structure = nestedStructures.at(nestedStructures.size()-1);}catch(...){}
							if (structure == pair<string,string>("tipos","sequence")){
								type.push_back(stringMap);
								stringMap.clear();
							}
							else if (structure == pair<string,string>("entidades","sequence")){
								entitys.push_back(stringMap);
								stringMap.clear();
							}

						}
				    	log("End Mapping","INFO");
				    	break;
			    	}
			    	/* Data */
					case YAML_ALIAS_EVENT:{
						printf("Got alias (anchor %s)\n", event.data.alias.anchor); break;
					}
					case YAML_SCALAR_EVENT:
					{
						scalarValue = string(reinterpret_cast<char*>(event.data.scalar.value));
						log(("Got scalar "+scalarValue),"INFO" );

						if ( key =="") key = scalarValue;
						else {
							value = scalarValue;
							structure = nestedStructures.at(1);
							//PANTALLA
							if (structure == pair<string,string>("pantalla","map")){
								screen.insert(pair<string,int>(key,atoi(value.c_str())));
							}
							//CONFIGURACION
							else if (structure == pair<string,string>("configuracion","map")){
								conf.insert(pair<string,int>(key,atoi(value.c_str())));
							}
							//TIPOS
							else if (structure == pair<string,string>("tipos","sequence")){
								structure = nestedStructures.at(2);
								if ( structure == pair<string,string>("","map")){
									stringMap.operator [](key) = value;
								}
							}

							//ESCENARIO
							else if (structure == pair<string,string>("escenario","map")){
								//stage
								try{structure = nestedStructures.at(2);}
								catch(...){stage.operator [](key) = value;}
								//entitys
								if (structure == pair<string,string>("entidades","sequence")){
									try{structure = nestedStructures.at(3);}catch(...){}
									if (structure == pair<string,string>("","map")){
										stringMap.operator [](key) = value;
									}
								}
								//mainCharacter
								if (structure == pair<string,string>("protagonista","map")){
									mainCharacter.operator [](key) = value;
								}

							}
							key = "";
						}
						break;
						}
					}
					if(event.type != YAML_STREAM_END_EVENT){
						yaml_event_delete(&event);

					}
				} while(event.type != YAML_STREAM_END_EVENT);

				/* END new code */

				Cleanup:
				yaml_event_delete(&event);
				yaml_parser_delete(&parser);
				fclose(fh);
				fclose (pFile);
				pFile = NULL;
				fh=NULL;
				}

	}catch(...){
		log("MALFORMED YAML FILE - Loading Default Settings","WARNING");
		cout << "MALFORMED YAML FILE - Loading Default Settings" << endl;
	}
}


map< string, int> * Loader::getScreen(){
	return &screen;
}

vector< map< string, string> >* Loader::getTypes(){
	return &type;
}

vector< map< string, string> >* Loader::getEntitys(){
	return &entitys;
}

map< string, int>* Loader::getConf(){
	return &conf;
}
map< string, string>* Loader::getStage(){
	return &stage;
}
map< string, string>* Loader::getMainCharacter(){
	return &mainCharacter;
}

void Loader::log(string msg, string type){
	time_t rawtime;
	struct tm * timeinfo;
	char strTime[80];
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	char *userName = getenv("LOGNAME");

	strftime(strTime,80,"%d-%m-%Y %I:%M:%S",timeinfo);
	fprintf (pFile, "%s %s Loader %s %s\n",userName, strTime, type.c_str(), msg.c_str());
}

void Loader::parserError(yaml_parser_t* parser){
	char* pChar;
	string str,str2;
	stringstream sstr,sstr2;
	switch (parser->error)
		{
		case YAML_MEMORY_ERROR:
			sprintf(pChar,"Memory error: Not enough memory for parsing");
			break;

		case YAML_READER_ERROR:
			if (parser->problem_value != -1) {
				sprintf(pChar, "Reader error: %s: #%X at %d\n", parser->problem,
						parser->problem_value, parser->problem_offset);
				str = string(pChar);
				log(str,"ERROR");
			} else {
				sprintf(pChar, "Reader error: %s at %d\n", parser->problem,
						parser->problem_offset);
				str = string(pChar);
					log(str,"ERROR");
			}
			break;
		case YAML_SCANNER_ERROR:
			if (parser->context) {
				sprintf(pChar,"Scanner error: %s at line %d, column %d\n"
                      "%s at line %d, column %d\n", parser->context,
                      parser->context_mark.line+1, parser->context_mark.column+1,
                      parser->problem, parser->problem_mark.line+1,
                      parser->problem_mark.column+1);
				str = string(pChar);
				log(str,"ERROR");
			}
			else {
				sprintf(pChar,"Scanner error: %s at line %d, column %d\n",
						parser->problem, parser->problem_mark.line+1,
						parser->problem_mark.column+1);
				str = string(pChar);
				log(str,"ERROR");

			}
			break;

		case YAML_PARSER_ERROR:
			if (parser->context) {
				sprintf(pChar,"Parser error: %s at line %d, column %d\n"
                      "%s at line %d, column %d\n", parser->context,
                      parser->context_mark.line+1, parser->context_mark.column+1,
                      parser->problem, parser->problem_mark.line+1,
                      parser->problem_mark.column+1);
				str = string(pChar);
				log(str,"ERROR");

			}
			else {
				sprintf(pChar,"Parser error: %s at line %d, column %d\n",
                      parser->problem, parser->problem_mark.line+1,
                      parser->problem_mark.column+1);
				str = string(pChar);
				log(str,"ERROR");

			}
			break;

		case YAML_COMPOSER_ERROR:
			if (parser->context) {
				sprintf(pChar,"Composer error: %s at line %d, column %d\n"
                      "%s at line %d, column %d\n", parser->context,
                      parser->context_mark.line+1, parser->context_mark.column+1,
                      parser->problem, parser->problem_mark.line+1,
                      parser->problem_mark.column+1);
				str = string(pChar);
				log(str,"ERROR");

			}
			else {
				sprintf(pChar,"Composer error: %s at line %d, column %d\n",
                      parser->problem, parser->problem_mark.line+1,
                      parser->problem_mark.column+1);
				str = string(pChar);
				log(str,"ERROR");

			}
			break;

		default:
			/* Couldn't happen.*/
			log("Internal error","ERROR");

			break;
		}
}


Loader::~Loader() {
/*	delete screen;
	delete conf;
	type = NULL; //no lo puedo destruir
	delete stage;
	delete entitys;
	delete mainCharacter;
*/
}
}
