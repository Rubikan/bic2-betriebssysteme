/**
 *
 * @file mypopen.h
 * Betriebssysteme Betriebssysteme mypopen File.
 * Beispiel 2
 *
 * @author Andreas Rubik <andreas.rubik@technikum-wien.at>
 * @author Anna Glock <ic14b070@technikum-wien.at>
 * @author Anna Huka <ic14b043@technikum-wien.at>
 *
 * @version 1.0
 * @date 2015/03/16
 *
 */

#ifndef MYPOPEN_H
#define MYPOPEN_H

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

FILE *mypopen(const char *command, const char *type);
int mypclose(FILE *stream);

#endif
