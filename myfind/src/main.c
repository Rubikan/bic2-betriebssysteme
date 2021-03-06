/**
 *
 * @file main.c
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

#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "parseopt.h"
#include "checks.h"

void do_dir(const char* dir_path, Option* first);
void do_file(const char* file_path, Option* first);
void print_usage(void);

/**
 * \brief main method of myfind
 * 		  calls parse_options and do_dir
 *
 * \return success if no option was wrong
 */
int main(int argc, char* argv[]) {
	Option* first = (Option *) malloc(sizeof(Option));
	int parsErr=0;

	char* startdir = (argv[1]!=NULL) ? ((strncmp(".", argv[1], 1) == 0 || strncmp("/", argv[1], 1) == 0) ? argv[1] : ".") : ".";
	parsErr = parse_options(argc, argv, first);

	switch(parsErr) {
		case 0:
			do_dir(startdir, first);
			break;
		case 98:
			break;
		case 99:
			print_usage();
			break;
	}
	if (parsErr) {
		return EXIT_FAILURE;
	}

	free_options(first);
	return EXIT_SUCCESS;
}

/**
 * \brief interrates through file directory's if dir_path is an dir
 *			if not it call the function do_file
 *
 * \param dir_path path to file
 * \param first first Option in the Optionslist
 *
 * \return nothing
 */
void do_dir(const char* dir_path, Option* first) {
	DIR *pDir;
	DIR *pSubDir;
	struct dirent *pDirentry;
	struct stat pStat;
	char file[512];
	int status;
	strcpy(file, dir_path);
	stat(file, &pStat);
	pDir = opendir(dir_path);

	if (pDir == NULL) {
		if S_ISREG(pStat.st_mode) {
			do_file(file, first);
		} else {
			printf("%s\n", dir_path);
		}
	} else {
		while ((pDirentry = readdir(pDir)) != NULL) {
			strcpy(file, dir_path);
			strcat(file, "/");
			strcat(file, pDirentry->d_name);
			status = stat(file, &pStat);

			if (status == -1)
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

/**
 * \brief checks all options for file
 *			if the file doesn't pass the checks the method stops the checking
 *
 * \param file_path path to file
 * \param first first Option in the Optionslist
 *
 * \return nothing
*/
void do_file(const char* file_path, Option* first) {
	Option* current = first;
	/*Benutzernamen und Gruppennamen für -ls*/
	char* username;
	char* groupname;
	struct passwd* userInfo;
	struct group* groupInfo;
	/*Zeit für -ls*/
	char format_date[200];
	time_t lastmod_time;
	struct tm* temp_time;
	/*Den Filename für die Namensüberprüfung extrahieren mit basename()*/
	char* temp = malloc(strlen(file_path)+1);
	char* file_name = NULL;
	struct stat pStat;
	strcpy(temp, file_path);
	file_name = basename(temp);
	/*Beinhaltet alle Informationen zu dem File*/
	stat(file_path, &pStat);

	while(current->next != NULL) {
		if (strncmp(current->name, "-name", 5) == 0) {
			if (check_name(file_name, current->argument) == 0)
				break;
		}
		else if (strncmp(current->name, "-user", 6) == 0) {
			if (check_user(pStat, current->argument) == 0)
				break;
		}
		else if (strncmp(current->name, "-type", 5) == 0) {
			if (check_type(pStat, current->argument[0]) == 0)
				break;
		}
		else if (strncmp(current->name, "-nouser", 7) == 0) {
			if (check_nouser(pStat) == 0)
				break;
		}
		else if (strncmp(current->name, "-path", 5) == 0) {
			if (check_path(file_path, current->argument) == 0)
				break;
		}
		else if (strncmp(current->name, "-print", 6) == 0) {
			printf("%s\n", file_path);
		}
		else if (strncmp(current->name, "-ls", 3) == 0) {
			/*Benutzername und Gruppenname auslesen*/
			userInfo = getpwuid(pStat.st_uid);
			groupInfo = getgrgid(pStat.st_gid);
			username = userInfo->pw_name;
			groupname = groupInfo->gr_name;
			/*Formatierten Zeit-String erzeugen*/
			lastmod_time = pStat.st_mtime;
      temp_time = localtime(&lastmod_time);
			if (strftime(format_date, sizeof(format_date), "%b %d %H:%M", temp_time) == 0) {
        fprintf(stderr, "Fehler bei strftime");
      	exit(EXIT_FAILURE);
      }

			printf("%6ld %4ld ", (long) pStat.st_ino, ((long) pStat.st_blocks)/2);
			printf((S_ISDIR(pStat.st_mode)) ? "d" : "-");
			printf((pStat.st_mode & S_IRUSR) ? "r" : "-");
			printf((pStat.st_mode & S_IWUSR) ? "w" : "-");
			printf((pStat.st_mode & S_IXUSR) ? "x" : "-");
			printf((pStat.st_mode & S_IRGRP) ? "r" : "-");
			printf((pStat.st_mode & S_IWGRP) ? "w" : "-");
			printf((pStat.st_mode & S_IXGRP) ? "x" : "-");
			printf((pStat.st_mode & S_IROTH) ? "r" : "-");
			printf((pStat.st_mode & S_IWOTH) ? "w" : "-");
			printf((pStat.st_mode & S_IXOTH) ? "x" : "-");
			printf("%4ld %s %8s %8ld %s %s\n", (long) pStat.st_nlink, username, groupname, (long) pStat.st_size,format_date, file_path);
		}
		current = current->next;
	}
}

/**
 *  \brief prints the usage of myfind
 *
 * \return nothing
 *
 */
void print_usage(void) {
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
