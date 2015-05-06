/**
 *
 * @file shared.c
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

#include "shared.h"

/**
 * \brief Prints the usage message for false arguments
 *
 * \return void
 */
void print_usage() {
    printf("Usage: [sender empfaenger] -m num\n");
}

/**
 * \brief Uses getopt to get the buffersize for the ring buffer
 *
 * \return integer Size the ringbuffer should have
 */
int get_buffersize(int argc, char* argv[]) {
  int buffersize;
  int opt;

  while ((opt = getopt(argc, argv, "m:")) != -1) {
    switch(opt) {
      case 'm':
        buffersize = atoi(optarg);
        break;
      default:
        print_usage();
        exit(EXIT_FAILURE);
    }
  }

  return buffersize;
}

void cleanup(int shmid, int* shmptr) {
  if (shmptr != NULL) {
    if (shmdt(shmptr) == -1) {
      /* FATAL ERROR: Shared memory could not be detached */
      printf("SCHWERER FEHLER: Shared memory konnte nicht ausgehängt werden!\n
              Der Shared memory Bereich mit der ID %d muss von Hand entfernt werden!\n", schmid);
      exit(EXIT_FAILURE);
    }
  }
  if (shmid != -1) {
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
      /* FATAL ERROR: Shared memory could not be removed */
      printf("SCHWERER FEHLER: Shared memory konnte nicht entfernt werden!\n
              Der Shared memory Bereich mit der ID %d muss von Hand entfernt werden!\n", schmid);
      exit(EXIT_FAILURE);
    }
  }
}
