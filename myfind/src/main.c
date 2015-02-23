#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include "parseopt.h"

void do_dir(const char* dir_name, Option* first);
void do_file(const char* file_name, Option* first);

int main(int argc, char* argv[]) {
	Option first;

	char* startdir = (strncmp(".", argv[1], 1) == 0 || strncmp("/", argv[1], 1) == 0) ? argv[1] : ".";
	parseopts(argc, argv, &first);

	do_dir(startdir, &first);

	return EXIT_SUCCESS;
}

void do_dir(const char* dir_name, Option* first) {
	DIR *pDir;
	pDir = opendir(dir_name);
	struct dirent *pDirentry;
	struct stat pStat;
	char file[512];
	int status;

	if (pDir == NULL) {
		printf("Cannot open directory %s!\n", startdir);
		return EXIT_FAILURE;
	}

	while ((pDirentry = readdir(pDir)) != NULL) {
		strcpy(file, dirname);
		strcat(file, "/");
		strcat(file, pDirentry->d_name);
		status = stat(file, &pStat);

		if(status == -1)
			printf("ERROR: %s\n", strerror(errno));

		if S_ISREG(pStat.st_mode) {
				//TODO: Wenn es ein regular File ist.
		}

		if S_ISDIR(pStat.st_mode) {
				//TODO: Wenn es ein Directory ist.
		}
	}

	closedir(pDir);
}

void do_file(const char* file_name, Option* first) {

}
