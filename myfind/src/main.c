#include "parseopt.h"

int main(int argc, char* argv[]) {
	Option first;
	char* startdir = (strncmp(".", argv[1], 1) == 0 || strncmp("/", argv[1], 1) == 0) ? argv[1] : ".";
	parseopts(argc, argv, &first);

	printf("Startdir: %s\n", startdir);
	while (first.next != NULL) {
		printf("%s ", first.next->name);
		if (first.next->argument != NULL)
			printf("%s\n", first.next->argument);
		else
			printf("\n");
		first = *first.next;		
	}

	return 0;
}
