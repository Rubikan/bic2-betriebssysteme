#ifndef CHECKS_H
#define CHECKS_H

#include <sys/stat.h>
#include <fnmatch.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>

int check_nouser(struct stat pStat);
int check_type(struct stat pStat, char type);
int check_user(struct stat pStat, char* usr_argument);
int check_name(const char* file_name, char* arg_pattern);
int check_path(const char* file_path, char* arg_pattern);

#endif
