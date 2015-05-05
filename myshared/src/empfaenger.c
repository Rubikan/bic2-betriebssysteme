/**
 *
 * @file empfaenger.c
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
#include "empfaenger.h"

/**
 * \brief main method of empfaenger
 *
 * \return EXIT_SUCCESS if the program ran correctly
 */
int main(int argc, char* argv[]) {
  int buffersize;
  int shmid;
  key_t shmkey;
  key_t semkey;
  uid_t uid;

  uid = getuid();
  shmkey = GET_KEY(uid, 0);
  semkey = GET_KEY(uid, 2);
  buffersize = get_buffersize(argc, argv);

  if ((shmid = shmget(shmkey, buffersize, 0660)) == -1) {
    /* ERROR: Shared Memory existiert nicht */
  }

  return EXIT_SUCCESS;
}
