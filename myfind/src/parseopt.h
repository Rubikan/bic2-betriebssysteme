#ifndef PARSEOPT_H
#define PARSEOPT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Option {
	char* name;
	char* argument;
	struct Option* next;
} Option;

int parse_options(int argc, char* argv[], Option* first);
void free_options(Option* option);
Option* create_option(Option* option, char* optionname, char* argument);

#endif
