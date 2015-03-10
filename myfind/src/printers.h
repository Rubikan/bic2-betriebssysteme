#ifndef PRINTERS_H
#define PRINTERS_H

#include <sys/stat.h>
#include <fnmatch.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>

void print_if_type(const char* file_path, struct stat pStat, char type);
void print_if_nouser(const char* file_path, struct stat pStat);
void print_if_name(const char* file_name, const char* file_path, char* arg_pattern);
void print_if_path(const char* file_path, char* arg_pattern);

#endif
