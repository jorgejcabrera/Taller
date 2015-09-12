/*
 * Parser.cpp
 *
 *  Created on: 4/9/2015
 *      Author: nico
 */

#include "Parser.h"

Parser::Parser() {
	// TODO Auto-generated constructor stub

}

void Parser::Parsear() {

  FILE *fh = fopen("mapConfig.yml", "r");
  yaml_parser_t parser;
  yaml_event_t  event;   /* New variable */

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
        switch (parser.error)
        {
            case YAML_MEMORY_ERROR:
                fprintf(stderr, "Memory error: Not enough memory for parsing\n");
                break;

            case YAML_READER_ERROR:
                if (parser.problem_value != -1) {
                    fprintf(stderr, "Reader error: %s: #%X at %d\n", parser.problem,
                            parser.problem_value, parser.problem_offset);
                }
                else {
                    fprintf(stderr, "Reader error: %s at %d\n", parser.problem,
                            parser.problem_offset);
                }
                break;

            case YAML_SCANNER_ERROR:
                if (parser.context) {
                    fprintf(stderr, "Scanner error: %s at line %d, column %d\n"
                            "%s at line %d, column %d\n", parser.context,
                            parser.context_mark.line+1, parser.context_mark.column+1,
                            parser.problem, parser.problem_mark.line+1,
                            parser.problem_mark.column+1);
                }
                else {
                    fprintf(stderr, "Scanner error: %s at line %d, column %d\n",
                            parser.problem, parser.problem_mark.line+1,
                            parser.problem_mark.column+1);
                }
                break;

            case YAML_PARSER_ERROR:
                if (parser.context) {
                    fprintf(stderr, "Parser error: %s at line %d, column %d\n"
                            "%s at line %d, column %d\n", parser.context,
                            parser.context_mark.line+1, parser.context_mark.column+1,
                            parser.problem, parser.problem_mark.line+1,
                            parser.problem_mark.column+1);
                }
                else {
                    fprintf(stderr, "Parser error: %s at line %d, column %d\n",
                            parser.problem, parser.problem_mark.line+1,
                            parser.problem_mark.column+1);
                }
                break;

            case YAML_COMPOSER_ERROR:
                if (parser.context) {
                    fprintf(stderr, "Composer error: %s at line %d, column %d\n"
                            "%s at line %d, column %d\n", parser.context,
                            parser.context_mark.line+1, parser.context_mark.column+1,
                            parser.problem, parser.problem_mark.line+1,
                            parser.problem_mark.column+1);
                }
                else {
                    fprintf(stderr, "Composer error: %s at line %d, column %d\n",
                            parser.problem, parser.problem_mark.line+1,
                            parser.problem_mark.column+1);
                }
                break;

            default:
                /* Couldn't happen. */
                fprintf(stderr, "Internal error\n");
                break;
        }
//       printf("Parser error %d\n", parser.error);
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
    case YAML_MAPPING_START_EVENT:  puts("<b>Start Mapping</b>");  break;
    case YAML_MAPPING_END_EVENT:    puts("<b>End Mapping</b>");    break;
    /* Data */
    case YAML_ALIAS_EVENT:  printf("Got alias (anchor %s)\n", event.data.alias.anchor); break;
    case YAML_SCALAR_EVENT: printf("Got scalar (value %s)\n", event.data.scalar.value); break;
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

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

