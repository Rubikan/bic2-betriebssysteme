#include "checks.h"

int check_type(struct stat pStat, char type) {
		switch(type) {
			case 'b':
				if S_ISBLK(pStat.st_mode)
					return 1;
				return 0;
				break;
			case 'c':
				if S_ISCHR(pStat.st_mode)
					return 1;
				return 0;
				break;
			case 'd':
				if S_ISDIR(pStat.st_mode)
					return 1;
				return 0;
				break;
			case 'p':
				if S_ISFIFO(pStat.st_mode)
					return 1;
				return 0;
				break;
			case 'f':
				if S_ISREG(pStat.st_mode)
					return 1;
				return 0;
				break;
			case 'l':
				if S_ISLNK(pStat.st_mode)
					return 1;
				return 0;
				break;
			case 's':
				if S_ISSOCK(pStat.st_mode)
					return 1;
				return 0;
				break;
			default:
				printf("find: Unbekanntes Argument von -type: %c\n", type);
				exit(EXIT_FAILURE);
		}
}

int check_nouser(struct stat pStat) {
  struct passwd* userInfo;
	userInfo = getpwuid(pStat.st_uid);

	if (userInfo == NULL){
		return 1;
	}
	return 0;
}

int check_name(const char* file_name, char* arg_pattern) {
  if (fnmatch(arg_pattern, file_name, 0) == 0) {
    return 1;
  }
	return 0;
}

int check_path(const char* file_path, char* arg_pattern) {
  if (fnmatch(arg_pattern, file_path, 0) == 0) {
    return 1;
  }
	return 0;
}

int check_user(struct stat pStat, char* usr_argument) {
	long uid;
	char* username;
	struct passwd* userInfo;

	userInfo = getpwuid(pStat.st_uid);
	if (userInfo == NULL) {
		return 0;
	}
	username = userInfo->pw_name;
	if (username == NULL) {
		return 0;
	}
	uid=strtol(usr_argument,NULL,10);
	if(uid==0){
		uid=-999;
	}
	if ((strncmp(username, usr_argument,50) != 0)){
		if (uid != (long)pStat.st_uid) {
			return 0;
		}
	}
	return 1;
}
