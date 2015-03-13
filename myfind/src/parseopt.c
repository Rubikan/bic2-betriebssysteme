#include <pwd.h>
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
int parse_options(int argc, char* argv[], Option* first) {
	struct passwd *pPasswd;
	int i = (argv[1]==NULL ? 1 : (strncmp(".", argv[1], 1) == 0 || strncmp("/", argv[1], 1) == 0) ? 2 : 1);
	int default_print = 1;
	Option* current = first;
	int err = 0;
	int uid;

	if (argc == 1) {
		err=99;
	}

	for (; i < argc; i++) {
		if (strcmp("-user", argv[i]) == 0) {
			pPasswd = getpwnam(argv[i+1]);
			if (pPasswd == NULL) {
				uid=strtol(argv[i+1],NULL,10);
				if(uid==0){
					uid=-999;
				}
				pPasswd =getpwuid(uid);
				if (pPasswd == NULL) {
					fprintf(stderr,"%s: '%s' is not the name of a known user\n", argv[0], argv[i+1]);
					err = 98;
					return err;
				} else {
					current = create_option(current, "-user", argv[++i]);
					current->next = (Option *) malloc(sizeof(Option));
					current = current->next;
			}
			} else {
				current = create_option(current, "-user", argv[++i]);
	      current->next = (Option *) malloc(sizeof(Option));
	      current = current->next;
			}
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
			/*printf("%s ist keine gueltige Aktion!\n", argv[i]);*/
			err=99;
		}
	}
	if (default_print) {
		current = create_option(current, "-print", NULL);
		current->next = (Option *) malloc(sizeof(Option));
		current = current->next;
	}
  current->next = NULL;
  return err;
	/*TODO: In meinen Augen bleibt hier irgendwo eine Node am Ende herumhängen.*/
	/*Aber bei Tests wo ich über alle Optionen durchiteriere und sie ausgehe gibt*/
	/*es keine Probleme. GGF noch schauen ob es Probleme gibt.*/
}

/**
 * \brief Fills a given Option struct with the needed values
 *
 * \param option Pointer to Option struct that should be filled
 * \param optionname Name the option should have (eg. -user)
 * \param argument Argument of the option. If no argument is needed (eg. -nouser) then
 *
 * \return Pointer to the option struct
 */
Option* create_option(Option* option, char* optionname, char* argument) {
	option->name = optionname;
	option->argument = argument;
	option->next = NULL;

	return option;
}

/**
 * \brief Iterates over the Option linked list and frees the memory.
 *
 * \param first Pointer to the first Option in the linked list of Options
 *
 * \return void
 */
void free_options(Option* first) {
	Option* next;

	while(first->next != NULL) {
		next = first->next;
		free(first);
		first = next;
	}
}
