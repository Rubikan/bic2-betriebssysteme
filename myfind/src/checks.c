/**
 *
 * @file checks.c
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

#include "checks.h"

/**
 *
 * \brief Checks if a file has the given type.
 *
 * \param pStat Pointer to the struct containing file information
 * \param type File type
 *
 * \return int 1 if true, 0 if false
 *
 */
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

/**
 *
 * \brief Checks if a file belongs to no user (no user existing with userid)
 *
 * \param pStat Pointer to the struct containing file information
 *
 * \return int 1 if true, 0 if false
 *
 */
int check_nouser(struct stat pStat) {
  struct passwd* userInfo;
	userInfo = getpwuid(pStat.st_uid);

	if (userInfo == NULL){
		return 1;
	}
	return 0;
}

/**
 *
 * \brief Checks if a file has the given name
 *
 * \param file_name Name of the file
 * \param arg_pattern Pattern against which the name is matched.
 *
 * \return int 1 if true, 0 if false
 *
 */
int check_name(const char* file_name, char* arg_pattern) {
  if (fnmatch(arg_pattern, file_name, 0) == 0) {
    return 1;
  }
	return 0;
}

/**
 *
 * \brief Checks if the path to a file matches a certain pattern.
 *
 * \param file_path Path that should be checked
 * \param arg_pattern Pattern against which the path is matched
 *
 * \return int 1 if true, 0 if false
 *
 */
int check_path(const char* file_path, char* arg_pattern) {
  if (fnmatch(arg_pattern, file_path, 0) == 0) {
    return 1;
  }
	return 0;
}

/**
 *
 * \brief Checks if a file belongs to a certain user (username or uid).
 *
 * \param pStat Pointer to the struct containing file information
 * \param usr_argument Username or uid for the check
 *
 * \return int 1 if true, 0 if false
 *
 */
int check_user(struct stat pStat, char* usr_argument) {
	long uid;
	char* username;
	struct passwd* userInfo;
	struct passwd* userInfo2;

	userInfo = getpwuid(pStat.st_uid);
	userInfo2 = getpwnam(usr_argument);
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
		if (userInfo2!=NULL || uid != (long)pStat.st_uid) {
			return 0;
		}
	}
	return 1;
}
