/*
 * Loader.cpp
 *
 *  Created on: 12/9/2015
 *      Author: nico
 */

#include "Loader.h"
#include <stack>

namespace std {

enum config { pantalla = 1, configuracion = 2, tipos = 3, escenario = 4 };


Loader::Loader() {
	screen = new map<string,int>();
	conf = new map<string,int>();

}

void Loader::Load(char* file) {
	FILE *fh = fopen(file, "r");
	yaml_parser_t parser;
	yaml_event_t  event;   /* New variable */
	string map,key,scalarValue;
	int value;
	config c;
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
	    case YAML_SEQUENCE_START_EVENT: puts("<b>Start Sequence</b>"); break;
	    case YAML_SEQUENCE_END_EVENT:   puts("<b>End Sequence</b>");   break;

	    case YAML_MAPPING_START_EVENT:
	    {
	    	puts("<b>Start Mapping</b>");
	    	map=scalarValue;
	    	break;
	    }
	    case YAML_MAPPING_END_EVENT:    puts("<b>End Mapping</b>");    break;
	    /* Data */
	    case YAML_ALIAS_EVENT:  printf("Got alias (anchor %s)\n", event.data.alias.anchor); break;
	    case YAML_SCALAR_EVENT:
	    {
	    	scalarValue = string(reinterpret_cast<char*>(event.data.scalar.value));

	    	if (map == "pantalla") c=pantalla;
	    	if (map == "configuracion") c=configuracion;
	    	if (map == "tipos") c=tipos;
	    	if (map == "escenario") c=escenario;

	    	switch (c)
	    	{

	    	case pantalla:
	    	{
	    		if ( key =="") key = scalarValue;
	    		else {
	    			value = atoi(scalarValue.c_str());
	    			screen->insert(pair<string,int>(key,value));
	    			key = "";
	    		}
	    		break;
	    	}

	    	case configuracion:
	    	{
	    		if ( key =="") key = scalarValue;
	    		else {
	    			value = atoi(scalarValue.c_str());
	    			conf->insert(pair<string,int>(key,value));
	    			key = "";
	    		}
	    		break;
	    	}

	    	case tipos:
	    	{
	    		break;
	    	}

	    	case escenario:
	    	{
	    		break;
	    	}

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

int Loader::getScreenWidth(){
	return screen->operator []("ancho");
}

int Loader::getScreenHeight(){
	return screen->operator []("alto");
}

int Loader::getMargenScroll(){
	return conf->operator []("margen_scroll");
}

int Loader::getVelPersonaje(){
	return conf->operator []("vel_personaje");
}


Loader::~Loader() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
