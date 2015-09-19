/*
 * Loader.cpp
 *
 *  Created on: 12/9/2015
 *      Author: nico
 */

#include "Loader.h"
#include <stack>
#include <map>
#include <string>
#include <stack>

Loader* Loader::instance = NULL;

namespace std {

enum config { pantalla = 1, configuracion = 2, tipos = 3, escenario = 4 };

Loader::Loader() {
	screen = new map<string,int>();
	conf = new map<string,int>();
	type = new vector< map< string, string> >();
	stage = new map< string, string> ();
	entitys = new vector< map< string, string> >();
	mainCharacter = new map< string, string>();

}

void Loader::load() {
	FILE *fh = fopen("mapConfig.yml", "r");
	yaml_parser_t parser;
	yaml_event_t  event;   /* New variable */
	map< string, string> stringMap;
	string map,key,scalarValue,value;
	vector<pair<string,string> > nestedStructures;
	pair<string,string> structure;


	  /* Initialize parser */
	  if(!yaml_parser_initialize(&parser))
	    fputs("Failed to initialize parser!\n", stderr);
	  if(fh == NULL)
	    fputs("Failed to open file!\n", stderr);

	  /* Set input file */
	  yaml_parser_set_input_file(&parser, fh);

	  /* START new code */
	  do {
	    if (!yaml_parser_parse(&parser, &event)) {
	       printf("Parser error %d\n", parser.error);
	       exit(EXIT_FAILURE);
	    }

	    switch(event.type)
	    {
	    case YAML_NO_EVENT: puts("No event!"); break;
	    /* Stream start/end */
	    case YAML_STREAM_START_EVENT: puts("STREAM START"); break;
	    case YAML_STREAM_END_EVENT:   puts("STREAM END");   break;
	    /* Block delimeters */
	    case YAML_DOCUMENT_START_EVENT: puts("<b>Start Document</b>"); break;
	    case YAML_DOCUMENT_END_EVENT:   puts("<b>End Document</b>");   break;
	    case YAML_SEQUENCE_START_EVENT:
	    	{

	    		nestedStructures.push_back(pair<string,string>(key,"sequence"));
	    		key="";
	    		puts("<b>Start Sequence</b>");
	    		break;
	    	}
	    case YAML_SEQUENCE_END_EVENT:
	    	{
	    		nestedStructures.pop_back();
	    		puts("<b>End Sequence</b>");
	    		break;
	    	}

	    case YAML_MAPPING_START_EVENT:
	    {
	    	puts("<b>Start Mapping</b>");
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
						type->push_back(stringMap);
						stringMap.clear();
					}
					else if (structure == pair<string,string>("entidades","sequence")){
						entitys->push_back(stringMap);
						stringMap.clear();
					}

				}
		    	puts("<b>End Mapping</b>");
		    	break;
	    	}
	    /* Data */
	    case YAML_ALIAS_EVENT:  printf("Got alias (anchor %s)\n", event.data.alias.anchor); break;
	    case YAML_SCALAR_EVENT:
	    {
	    	scalarValue = string(reinterpret_cast<char*>(event.data.scalar.value));
	    	printf("Got scalar %s\n", event.data.scalar.value);

    		if ( key =="") key = scalarValue;
    		else {
    			value = scalarValue;
    			structure = nestedStructures.at(1);
    			//PANTALLA
    			if (structure == pair<string,string>("pantalla","map")){
    				screen->insert(pair<string,int>(key,atoi(value.c_str())));
    			}
    			//CONFIGURACION
    			else if (structure == pair<string,string>("configuracion","map")){
    		    	conf->insert(pair<string,int>(key,atoi(value.c_str())));
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
    				catch(...){stage->operator [](key) = value;}
    				//entitys
    				if (structure == pair<string,string>("entidades","sequence")){
        				try{structure = nestedStructures.at(3);}catch(...){}
        				if (structure == pair<string,string>("","map")){
        					stringMap.operator [](key) = value;
        				}
    				}
    				//mainCharacter
    				if (structure == pair<string,string>("protagonista","map")){
    					mainCharacter->operator [](key) = value;
    				}

    		    }
        		key = "";
    		}

    	break;
	    }
	    }
	    if(event.type != YAML_STREAM_END_EVENT)
	      yaml_event_delete(&event);
	  } while(event.type != YAML_STREAM_END_EVENT);
	  yaml_event_delete(&event);
	  /* END new code */

	  /* Cleanup */
	  yaml_parser_delete(&parser);
	  fclose(fh);

}
}

int Loader::getScreenWidth(){
	return screen->operator []("ancho");
}

int Loader::getScreenHeight(){
	return screen->operator []("alto");
}

vector< map< string, string> >* Loader::getTypes(){
	return type;
}

vector< map< string, string> >* Loader::getEntitys(){
	return entitys;
}

map< string, int>* Loader::getConf(){
	return conf;
}
map< string, string>* Loader::getStage(){
	return stage;
}
map< string, string>* Loader::getMainCharacter(){
	return mainCharacter;
}


Loader* Loader::GetInstance() {
	if (!instance) {
		instance = new Loader();
		instance->load();
	}
	return instance;
}


Loader::~Loader() {
	//Loader* Loader::instance = NULL;
}

/* namespace std */
