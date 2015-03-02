#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include "parseopt.h"

void do_dir(const char* dir_name, Option* first);
void do_file(const char* file_name, Option* first);

int main(int argc, char* argv[]) {
	Option* first = (Option *) malloc(sizeof(Option));

	/*TODO: Falls kein Directory UND keine Options angegeben werden passiert ein Segfault.*/
	/*Generell muss der Teil hier noch stark überarbeitet werden, eine Directory Angabe in find*/
	/*muss nicht zwanghaft mit "." oder "/" anfangen.*/
	char* startdir = (strncmp(".", argv[1], 1) == 0 || strncmp("/", argv[1], 1) == 0) ? argv[1] : ".";
	parse_options(argc, argv, first);

	do_dir(startdir, first);

	free_options(first);
	return EXIT_SUCCESS;
}

void do_dir(const char* dir_name, Option* first) {
	DIR *pDir;
	DIR *pSubDir;
	struct dirent *pDirentry;
	struct stat pStat;
	char file[512];
	int status;
	pDir = opendir(dir_name);

	if (pDir == NULL) {
		printf("Cannot open directory %s!\n", dir_name);
	}

	while ((pDirentry = readdir(pDir)) != NULL) {
		strcpy(file, dir_name);
		strcat(file, "/");
		strcat(file, pDirentry->d_name);
		status = stat(file, &pStat);

		if(status == -1)
			printf("ERROR: %s\n", strerror(errno));

		if S_ISREG(pStat.st_mode) {
				do_file(file, first);
		}

		if S_ISDIR(pStat.st_mode) {
				printf("%s\n", dir_name);
				/*Überspringt das rekursive durchlaufen der . und .. Ordner*/
				if (!(strncmp(pDirentry->d_name, ".", 1) == 0 || strncmp(pDirentry->d_name, "..", 2) == 0)) {
					pSubDir = opendir(file);
					do_dir(file, first);
					closedir(pSubDir);
				}
			}
		}

	closedir(pDir);
}

void do_file(const char* file_name, Option* first) {
	Option* current = first;
	struct stat pStat;
	/*Beinhaltet alle Informationen zu dem File*/
	/*Folien "Linux Filesystem" ab Seite 16.*/
	stat(file_name, &pStat);

	while(current->next != NULL) {
		if (strncmp(current->name, "-print", 6) == 0)
			printf("%s\n", file_name);
		current = current->next;
	}
}
