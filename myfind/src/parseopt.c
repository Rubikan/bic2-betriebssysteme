#include "parseopt.h"

/**
 * \brief Parses the argv[] into a linked list of options.
 *
 * \param argc The number of arguments
 * \param argv The arguments itselves (including the program name in argv[0])
 * \param first Pointer to an option (the first option in the list)
 *
 * \return void
 */

void parse_options(int argc, char* argv[], Option* first) {
	int i = (strncmp(".", argv[1], 1) == 0 || strncmp("/", argv[1], 1) == 0) ? 2 : 1;
	int default_print = 1;
	Option* current = first;

	for (; i < argc; i++) {
		if (strcmp("-user", argv[i]) == 0) {
			current = create_option(current, "-user", argv[++i]);
      current->next = (Option *) malloc(sizeof(Option));
      current = current->next;
		}
		else if (strcmp("-name", argv[i]) == 0) {
      current = create_option(current, "-name", argv[++i]);
      current->next = (Option *) malloc(sizeof(Option));
      current = current->next;
		}
		else if (strcmp("-type", argv[i]) == 0) {
      current = create_option(current, "-type", argv[++i]);
      current->next = (Option *) malloc(sizeof(Option));
      current = current->next;
		}
		else if (strcmp("-path", argv[i]) == 0) {
      current = create_option(current, "-path", argv[++i]);
      current->next = (Option *) malloc(sizeof(Option));
      current = current->next;
		}
		else if (strcmp("-print", argv[i]) == 0) {
      current = create_option(current, "-print", NULL);
      current->next = (Option *) malloc(sizeof(Option));
      current = current->next;
			default_print = 0;
		}
		else if (strcmp("-ls", argv[i]) == 0) {
      current = create_option(current, "-ls", NULL);
      current->next = (Option *) malloc(sizeof(Option));
      current = current->next;
      default_print = 0;
		}
		else if (strcmp("-nouser", argv[i]) == 0) {
      current = create_option(current, "-nouser", NULL);
      current->next = (Option *) malloc(sizeof(Option));
      current = current->next;
		}
		else {
			printf("%s ist keine gueltige Aktion!\n", argv[i]);
		}
	}
	if (default_print) {
		current = create_option(current, "-print", NULL);
		current->next = (Option *) malloc(sizeof(Option));
		current = current->next;
	}
  current->next = NULL;
	/*TODO: In meinen Augen bleibt hier irgendwo eine Node am Ende herumhängen.*/
	/*Aber bei Tests wo ich über alle Optionen durchiteriere und sie ausgehe gibt*/
	/*es keine Probleme. GGF noch schauen ob es Probleme gibt.*/
}

Option* create_option(Option* option, char* optionname, char* argument) {
	option->name = optionname;
	option->argument = argument;
	option->next = NULL;

	return option;
}

void free_options(Option* first) {
	Option* next;

	while(first->next != NULL) {
		next = first->next;
		free(first);
		first = next;
	}
}
