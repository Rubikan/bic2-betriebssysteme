/**
 *
 * @file shared.h
 * Betriebssysteme myshared File.
 * Beispiel 3
 *
 * @author Andreas Rubik <andreas.rubik@technikum-wien.at>
 * @author Anna Glock <ic14b070@technikum-wien.at>
 * @author Anna Huka <ic14b043@technikum-wien.at>
 *
 * @version 1.0
 * @date 2015/05/04
 *
 */

#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <sem182.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>
#include <getopt.h>

#define GET_KEY(uid, offset) ftok("/etc/hosts",(1000 * uid + offset))

void print_usage(void);
void cleanup(int shmid, int* shmptr);
int get_buffersize(int argc, char* argv[]);

#endif
