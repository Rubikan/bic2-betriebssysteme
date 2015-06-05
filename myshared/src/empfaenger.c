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
  int shmid = -99;
  int semid_one = -99;
  int semid_two = -99;
  int* shmptr = NULL;
  key_t shmkey;
  key_t semkey_one;
  key_t semkey_two;
  uid_t uid;
  int aktuellesEl=-1;
  char ch;
  int hasNext=1;

  buffersize = parse_arguments(argc, argv);
  uid = getuid();
  shmkey = GET_KEY(uid, 0);
  semkey_one = GET_KEY(uid, 1);
  semkey_two = GET_KEY(uid, 2);

  /* Register signal handlers */
  /*signal(SIGSTOP, sig_handler);
  signal(SIGCONT, sig_handler);*/

  /* Get ID to first semaphore */
  if ((semid_one = semgrab(semkey_one)) == -1) {
    if ((semid_one = seminit(semkey_one, 0660, buffersize)) == -1) {
      /* ERROR: Error when getting id of semaphore one */
      printf("Der erste Semaphor konnte nicht angelegt werden!\n");
      exit(EXIT_FAILURE);
    }
  }

  /* Get ID to second semaphore */
  if ((semid_two = semgrab(semkey_two)) == -1) {
    if ((semid_two = seminit(semkey_two, 0660, 0)) == -1) {
      /* ERROR: Error when getting id of semaphore two */
      printf("Der zweite Semaphor konnte nicht angelegt werden!\n");
      exit(EXIT_FAILURE);
    }
  }

  if (P(semid_two) == -1) {
	  printf("cleanup: 1");
    cleanup(-1, NULL, semid_one, semid_two);
    exit(EXIT_FAILURE);
  }
  /* Create shared memory */
  if ((shmid = shmget(shmkey, buffersize, 0660)) == -1) {
	  /* printf("shared memory exists not emp, shmkey: %d\n", shmkey); */
    if ((shmid = shmget(shmkey, buffersize, 0660|IPC_CREAT|IPC_EXCL)) == -1) {
      /* ERROR: Shared memory already exists or couldn't be created */
      printf("Shared Memory wurde schon angelegt oder konnte nicht angelegt werden!\n");
      exit(EXIT_FAILURE);
    }
  }

  /* Get pointer to the shared memory */
  if ((shmptr = shmat(shmid, NULL, 0)) == (int*) -1) {
    /* ERROR: Error when getting pointer to shared memory */
    printf("Der Pointer auf den Shared Memory konnte nicht angelegt werden!\n");
    exit(EXIT_FAILURE);
  }

  if (V(semid_one) == -1) {
	  printf("cleanup: 2");
    cleanup(shmid, shmptr, semid_one, semid_two);
    exit(EXIT_FAILURE);
  }

  do {
    /* Loop for pausing the process */
    /*do {
      errno = 0;
      P(semid_two);
    } while (errno == EINTR);*/

	
    do {
      errno = 0;   
	  if (P(semid_two) == -1) {
		if(errno != EINTR){
			timestamp();
			printf("cleanup: 3(do while)\n");
			cleanup(shmid, shmptr, semid_one, semid_two);
			exit(EXIT_FAILURE);
		}
	  }
	  if(errno == EINTR){
		 /* printf("do while; errno == EINTR\n"); */
		 if (V(semid_two) == -1) {
			printf("cleanup: 4(do while)\n");
			cleanup(shmid, shmptr, semid_one, semid_two);
			exit(EXIT_FAILURE);
		 }		  
	  }
    } while (errno == EINTR);
	
	  aktuellesEl++;
    /*if (P(semid_two) == -1) {
	    printf("cleanup: 3");
      cleanup(shmid, shmptr, semid_one, semid_two);
      exit(EXIT_FAILURE);
    }*/

    /* Critical section begin */
	  if (shmptr[aktuellesEl%buffersize] != 256) {
	    ch = shmptr[aktuellesEl%buffersize];
	    shmptr[aktuellesEl%buffersize] = '\0';
	    /*if (write(STDOUT_FILENO, &ch, 1) == -1) {*/
	    if (putc(ch, stdout) == -1) {
			  printf("Fehler beim Schreiben auf STDOUT! Errno: %d", errno);
			  exit(EXIT_FAILURE);
      }
	  } else {
		  /* printf("\ngot EOF\n"); */
		  hasNext = 0;
	  }
	  /* Critical section end*/

    if (V(semid_one) == -1) {
	    printf("cleanup: 4");
      cleanup(shmid, shmptr, semid_one, semid_two);
      exit(EXIT_FAILURE);
    }
  } while(hasNext);

  /* printf("cleanup: 5"); */
  cleanup(shmid, shmptr, semid_one, semid_two);
  return EXIT_SUCCESS;
}
