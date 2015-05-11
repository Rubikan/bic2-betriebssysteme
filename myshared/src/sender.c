/**
 *
 * @file sender.c
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
#include "sender.h"
#include <errno.h>

/**
 * \brief main method of sender
 *
 * \return EXIT_SUCCESS if the program ran correctly
 */
int main(int argc, char* argv[]) {
  int buffersize;
  int shmid;
  int* shmptr;
  key_t shmkey;
  key_t semkey;
  uid_t uid;

  uid = getuid();
  shmkey = GET_KEY(uid, 0);
  semkey = GET_KEY(uid, 1);
  buffersize = get_buffersize(argc, argv);

  /* Create shared memory */
  if ((shmid = shmget(shmkey, buffersize, 0660|IPC_CREAT|IPC_EXCL)) == -1) {
    /* ERROR: Shared memory already exists or couldn't be created */
    printf("Shared Memory wurde schon angelegt oder konnte nicht angelegt werden!\n");
    exit(EXIT_FAILURE);
  }
  /* Get pointer to the shared memory */
  if ((shmptr = shmat(shmid, NULL, 0)) == (int*) -1) {
    /* ERROR: Error when getting pointer to shared memory */
    printf("Der Pointer auf den Shared Memory konnte nicht angelegt werden!\n");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
