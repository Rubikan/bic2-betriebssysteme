#ifndef PRINTERS_H
#define PRINTERS_H

#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>

void print_if_type(char type, const char* file_path, struct stat pStat);
void print_if_nouser(const char* file_path, struct stat pStat);

#endif
