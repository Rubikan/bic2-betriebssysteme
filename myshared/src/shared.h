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

#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sem182.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define GET_KEY(uid, offset) ftok("/etc/hosts",(1000 * uid + offset))

void timestamp(void);
void sig_handler(int signo);
void print_usage(char* program);
void cleanup(int shmid, int* shmptr, int semid_one, int semid_two);
int parse_arguments(int argc, char* argv[]);

#endif
