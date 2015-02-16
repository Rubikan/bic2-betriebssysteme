#include <stdio.h>
#include "parseopt.h"

int main(int argc, char* argv[]) {
	Options options;
	parseopts(argc, argv, &options);

	return 0;
}
