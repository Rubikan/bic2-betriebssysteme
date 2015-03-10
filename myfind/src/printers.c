#include "printers.h"

void print_if_type(const char* file_path, char type, struct stat pStat) {
		switch(type) {
			case 'b':
				if S_ISBLK(pStat.st_mode)
					printf("%s\n", file_path);
				break;
			case 'c':
				if S_ISCHR(pStat.st_mode)
					printf("%s\n", file_path);
				break;
			case 'd':
				if S_ISDIR(pStat.st_mode)
					printf("%s\n", file_path);
				break;
			case 'p':
				if S_ISFIFO(pStat.st_mode)
					printf("%s\n", file_path);
				break;
			case 'f':
				if S_ISREG(pStat.st_mode)
					printf("%s\n", file_path);
				break;
			case 'l':
				if S_ISLNK(pStat.st_mode)
					printf("%s\n", file_path);
				break;
			case 's':
				if S_ISSOCK(pStat.st_mode)
					printf("%s\n", file_path);
				break;
			default:
				printf("find: Unbekanntes Argument von -type: %c\n", type);
				break;
		}
}

void print_if_nouser(const char* file_path, struct stat pStat) {
  struct passwd* userInfo;
	userInfo = getpwuid(pStat.st_uid);

	if (userInfo == NULL){
		printf("%s\n", file_path);
	}
}
