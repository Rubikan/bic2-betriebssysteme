#include <stdio.h>
#include <string.h>
#include "parseopt.h"

void parseopts(int argc, char* argv[], Options* options) {
	int i;

	if (strncmp(".", argv[1], 1) == 0 || strncmp("/", argv[1], 1) == 0) {
		options->start_dir = argv[1];
		i = 2;
	} else {
		options->start_dir = ".";
		i = 1;
	}
	options->print = 0;
	options->ls = 0;
	options->nouser = 0;
	options->user = 0;
	options->name = 0;
	options->type = 0;
	options->path = 0;

	for (; i < argc; i++) {
		if (strcmp("-user", argv[i]) == 0) {
			options->user = 1;
			options->suser = argv[++i];
		}
		else if (strcmp("-name", argv[i]) == 0) {
			options->name = 1;
			options->sname = argv[++i];
		}
		else if (strcmp("-type", argv[i]) == 0) {
			options->type = 1;
			options->stype = argv[++i];
		}
		else if (strcmp("-path", argv[i]) == 0) {
			options->path = 1;
			options->spath = argv[++i];
		}
		else if (strcmp("-print", argv[i]) == 0) {
			options->print = 1;
		}
		else if (strcmp("-ls", argv[i]) == 0) {
			options->ls = 1;
		}
		else if (strcmp("-nouser", argv[i]) == 0) {
			options->nouser = 1;
		}
		else {
			printf("%s ist keine gueltige Aktion!", argv[i]);
		}
	}
}
