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
 * \param argc Argument counter
 * \param argv Argument vector
 *
 * \return integer Size the ringbuffer should have
 */
int get_buffersize(int argc, char* argv[]) {
  int opt;
  int buffersize = -1;

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

/**
 * \brief Cleans up the ids and pointers of shared memory
 *
 * \param schmid    The ID of the shared memory that should be detached.
 *                  -1 if you don't want to detach a shared memory.
 * \param shmptr    The pointer to the shared memory you want to remove.
 *                  NULL if you don't want to remove a shared memory.
 * \param semid_one The id of the semaphore that should be removed.
 *                  -1 if you don't want to remove a semaphore.
 * \param semid_two The id of the semaphore that should be removed.
 *                  -1 if you don't want to remove a semaphore.
 *
 * \return void
 */
void cleanup(int shmid, int* shmptr, int semid_one, int semid_two) {
  if (shmptr != NULL) {
    if (shmdt(shmptr) == -1) {
      /* FATAL ERROR: Shared memory could not be detached */
      printf("SCHWERER FEHLER: Shared memory konnte nicht ausgehängt werden!\nDer Shared memory Bereich mit der ID %d muss von Hand entfernt werden!\n", shmid);
      exit(EXIT_FAILURE);
    }
  }
  if (shmid != -1) {
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
      /* FATAL ERROR: Shared memory could not be removed */
      printf("SCHWERER FEHLER: Shared memory konnte nicht entfernt werden!\nDer Shared memory Bereich mit der ID %d muss von Hand entfernt werden!\n", shmid);
      exit(EXIT_FAILURE);
    }
  }
  if (semid_one != -1) {
    if (semrm(semid_one) == -1) {
      /* FATAL ERROR: Semaphore could not be removed */
      printf("SCHWERER FEHLER: Semaphor mit der ID %d konnte nicht entfernt werden!", semid_one);
      exit(EXIT_FAILURE);
    }
  }
  if (semid_two != -1) {
    if (semrm(semid_two) == -1) {
      /* FATAL ERROR: Semaphore could not be removed */
      printf("SCHWERER FEHLER: Semaphor mit der ID %d konnte nicht entfernt werden!", semid_two);
      exit(EXIT_FAILURE);
    }
  }
}
