/**
 *
 * @file parseopt.h
 * Betriebssysteme Betriebssysteme myfind File.
 * Beispiel 1
 *
 * @author Andreas Rubik <andreas.rubik@technikum-wien.at>
 * @author Anna Glock <ic14b070@technikum-wien.at>
 * @author Anna Huka <ic14b043@technikum-wien.at>
 *
 * @version 1.0
 * @date 2015/03/13
 *
 */

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
