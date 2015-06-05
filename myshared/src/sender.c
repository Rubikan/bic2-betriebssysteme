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
  int ch;
  key_t shmkey;
  key_t semkey_one;
  key_t semkey_two;
  uid_t uid;
  int aktuellesEl = 0;
  int countSemOne=0;

  buffersize = parse_arguments(argc, argv);
  uid = getuid();
  shmkey = GET_KEY(uid, 0);
  semkey_one = GET_KEY(uid, 1);
  semkey_two = GET_KEY(uid, 2);
  countSemOne=buffersize;

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

  if (P(semid_one) == -1) {
	  printf("cleanup: 1");
    cleanup(-1, NULL, semid_one, semid_two);
    exit(EXIT_FAILURE);
  }

  /* Create shared memory */
  if ((shmid = shmget(shmkey, buffersize, 0660)) == -1) {
	  /* printf("shared memory exists not sen, shmkey: %d\n", shmkey);*/
    if ((shmid = shmget(shmkey, buffersize, 0660|IPC_CREAT|IPC_EXCL)) == -1) {
      /* ERROR: Shared memory already exists or couldn't be created */
      printf("Shared Memory wurde schon angelegt oder konnte nicht angelegt werden!\n");
      exit(EXIT_FAILURE);
    }
  }

  /* Get pointer to the shared memory */
  if ((shmptr = shmat(shmid, NULL, 1)) == (int*) -1) {
    /* ERROR: Error when getting pointer to shared memory */
    printf("Der Pointer auf den Shared Memory konnte nicht angelegt werden!\n");
    exit(EXIT_FAILURE);
  }

  if (V(semid_two) == -1) {
	  printf("cleanup: 2");
    cleanup(shmid, shmptr, semid_one, semid_two);
    exit(EXIT_FAILURE);
  }
  /* Loop that reads from STDIN and writes it to the shared memory */
  /* while(read(STDIN_FILENO, &ch, 1) > 0) { */
  while((ch = getc(stdin)) > 0) {
    /* Loop for pausing the process */
    do {
      errno = 0;    
	  /*printf("before grab sem one during do while\n");
	  if ((semid_one = semgrab(semkey_one)) == -1) {
		  printf("was not able to grab sem one during do while\n");
	  }
      if ((semid_one = semgrab(semkey_one)) == -1) {
	      printf("ch: %d\n",aktuellesEl);
	      printf("semkey one not here\n");
      }*/
	  if (P(semid_one) == -1) {
		if(errno == EINTR){
			/*if ((semid_one = semgrab(semkey_one)) == -1) {
				printf("was not able to grab sem one during do while\n");			
			}*/
		}else{
		timestamp();
		printf("cleanup: 3(do while)\n");
		cleanup(shmid, shmptr, semid_one, semid_two);
		exit(EXIT_FAILURE);
		}
	  }
	  if(errno == EINTR){
		 /* printf("do while; errno == EINTR\n"); */
		 if (V(semid_one) == -1) {
			printf("cleanup: 4(do while)\n");
			cleanup(shmid, shmptr, semid_one, semid_two);
			exit(EXIT_FAILURE);
		 }		  
	  }
    } while (errno == EINTR);



    /* Critical Section */
	  if(shmptr[aktuellesEl % buffersize] == '\0'){
		  shmptr[aktuellesEl % buffersize] = ch;
		  aktuellesEl++;
	  }

    if (V(semid_two) == -1) {
	  printf("cleanup: 4\n");
      cleanup(shmid, shmptr, semid_one, semid_two);
      exit(EXIT_FAILURE);
    }
  }
  /* Printing 256 as EOF indicator to shared memory */
  if (P(semid_one) == -1) {
	timestamp();
	printf("cleanup: 5\n");
    cleanup(shmid, shmptr, semid_one, semid_two);
    exit(EXIT_FAILURE);
  }

  /* Critical Section */
	if (shmptr[aktuellesEl % buffersize] == '\0'){
	  shmptr[aktuellesEl % buffersize] = 256;
	  aktuellesEl++;
	}

  if (V(semid_two) == -1) {
	  printf("cleanup: 6");
    cleanup(shmid, shmptr, semid_one, semid_two);
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
