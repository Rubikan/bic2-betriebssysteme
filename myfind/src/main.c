#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <fnmatch.h>
#include <pwd.h>
#include "parseopt.h"

void do_dir(const char* dir_path, Option* first);
void do_file(const char* file_path, Option* first);

int main(int argc, char* argv[]) {
	Option* first = (Option *) malloc(sizeof(Option));
	int parsErr=0;

	/*TODO: Falls kein Directory UND keine Options angegeben werden passiert ein Segfault.*/
	/*Generell muss der Teil hier noch stark überarbeitet werden, eine Directory Angabe in find*/
	/*muss nicht zwanghaft mit "." oder "/" anfangen.*/
	char* startdir = (argv[1]!=NULL) ? ((strncmp(".", argv[1], 1) == 0 || strncmp("/", argv[1], 1) == 0) ? argv[1] : ".") : ".";
	parsErr=parse_options(argc, argv, first);

	if(!parsErr){
		do_dir(startdir, first);
	}else{
		printf("\nDie Eingabe wurde nicht erkannt\n");
		printf("Bitte rufen Sie myfind wie folgt auf: \n");
		printf("myfind <directory> [ <aktion> ] ...\n");
		printf("Moegliche aktionen\n");
		printf("'-user'\n");
		printf("'-name'\n");
		printf("'-type'\n");
		printf("'-print'\n");
		printf("'-ls'\n");
		printf("'-nouser'\n");
		printf("'-path'\n");
	}

	free_options(first);
	return EXIT_SUCCESS;
}

void do_dir(const char* dir_path, Option* first) {
	DIR *pDir;
	DIR *pSubDir;
	struct dirent *pDirentry;
	struct stat pStat;
	char file[512];
	int status;
	pDir = opendir(dir_path);

	if (pDir == NULL) {
		printf("Cannot open directory %s!\n", dir_path);
	} else {
		while ((pDirentry = readdir(pDir)) != NULL) {
			strcpy(file, dir_path);
			strcat(file, "/");
			strcat(file, pDirentry->d_name);
			status = stat(file, &pStat);

			if(status == -1)
				printf("ERROR: %s\n", strerror(errno));

			if S_ISDIR(pStat.st_mode) {
				do_file(file, first);
				/*Überspringt das rekursive durchlaufen der . und .. Ordner*/
				if (!(strncmp(pDirentry->d_name, ".", 1) == 0 || strncmp(pDirentry->d_name, "..", 2) == 0)) {
					pSubDir = opendir(file);
					do_dir(file, first);
					closedir(pSubDir);
				}
			}

			if S_ISREG(pStat.st_mode) {
				do_file(file, first);
			}
		}
	}
	closedir(pDir);
}

void do_file(const char* file_path, Option* first) {
	Option* current = first;
	/*Den Filename für die Namensüberprüfung extrahieren mit basename()*/
	char* temp = malloc(strlen(file_path)+1);
	char* file_name = NULL;
	struct stat pStat;
	char *time;
	size_t max=50;
	/*MM DD HH:MI*/
	const char *format="%b %d H:M";
	strcpy(temp, file_path);
	file_name = basename(temp);
	/*Beinhaltet alle Informationen zu dem File*/
	/*Folien "Linux Filesystem" ab Seite 16.*/
	stat(file_path, &pStat);

	while(current->next != NULL) {
		if (strncmp(current->name, "-name", 5) == 0) {
			if (fnmatch(current->argument, file_name, 0) == FNM_NOMATCH) {
				break;
			}
		}else if (strncmp(current->name, "-print", 6) == 0) {
			printf("%s\n", file_path);
		}else if (strncmp(current->name, "-ls", 6) == 0) {
			/*printf für -ls eingefügt*/
			/*TODO: übergabeparameter für -ls festlegen*/
			/*Nummer des Inodes, Anzahl der Blocks, Permissions, 
			Anzahl der Links, Owner, Group, Last Modification Time 
			und den Namen des Directoryeintrags */
			/*strftime(time, max, format, pStat.st_mtime);*/
			printf("%8lu %4d %s %4d %s    %s %8d %s %s\n", pStat.st_ino,0,"",0,"","",0,"","");
			/*strftime(char *s, size_t max, const char *format,
                       const struct tm *tm);*/
		}else if (strncmp(current->name, "-user", 6) == 0) {
			if(current->argument == getpwnam()){
				
			}
		}else if (strncmp(current->name, "-type", 6) == 0) {
			printf("%s\n", file_path);
		}else if (strncmp(current->name, "-nouser", 6) == 0) {
			printf("%s\n", file_path);
		}else if (strncmp(current->name, "-path", 6) == 0) {
			if (fnmatch(current->argument, file_path, 0) == FNM_NOMATCH) {
				break;
			}
		}
		current = current->next;
	}
}
