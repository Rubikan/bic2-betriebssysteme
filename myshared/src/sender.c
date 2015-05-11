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

/**
 * \brief main method of sender
 *
 * \return EXIT_SUCCESS if the program ran correctly
 */
int main(int argc, char* argv[]) {
  int buffersize;
  int shmid;
  int semid_one;
  int semid_two;
  int* shmptr;
  key_t shmkey;
  key_t semkey_one;
  key_t semkey_two;
  uid_t uid;

  uid = getuid();
  shmkey = GET_KEY(uid, 0);
  semkey_one = GET_KEY(uid, 1);
  semkey_two = GET_KEY(uid, 2);
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
  /* Get ID to first semaphore */
  if ((semid_one = seminit(semkey_one, 0660, 0)) == -1) {
    /* ERROR: Error when getting id of semaphore one */
    printf("Der erste Semaphor konnte nicht angelegt werden!\n");
    exit(EXIT_FAILURE);
  }
  /* Get ID to second semaphore */
  if ((semid_two = seminit(semkey_two, 0660, 0)) == -1) {
    /* ERROR: Error when getting id of semaphore two */
    printf("Der zweite Semaphor konnte nicht angelegt werden!\n");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
