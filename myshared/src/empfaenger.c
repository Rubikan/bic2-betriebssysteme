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
#include <string.h>

/**
 * \brief main method of empfaenger
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
  int aktuellesEl;
  char ch;

  if(argc < 2){
    printf("Es wurde keine Buffersize angegeben!\n");
    exit(EXIT_FAILURE);
  } else if(argc > 2){
	  if(!strcmp(argv[1],"-m")){
		 if(argc > 3){
			printf("Es wurde keine Buffersize angegeben!\n");
			exit(EXIT_FAILURE);
		 }
	  }
  }

  uid = getuid();
  shmkey = GET_KEY(uid, 0);
  semkey_one = GET_KEY(uid, 1);
  semkey_two = GET_KEY(uid, 2);
  buffersize = get_buffersize(argc, argv);


  /* Get access to the already created shared memory */
  if ((shmid = shmget(shmkey, buffersize, 0660)) == -1) {
    /* ERROR: Shared memory is not existing */
    printf("Es wurde noch kein Shared Memory angelegt!\n");
    exit(EXIT_FAILURE);
  }
  /* Get pointer to the shared memory */
  if ((shmptr = shmat(shmid, NULL, 0)) == (int*) -1) {
    /* ERROR: Error when getting pointer to shared memory */
    printf("Der Pointer auf den Shared Memory konnte nicht angelegt werden!\n");
    exit(EXIT_FAILURE);
  }
  /* Get ID to first semaphore */
  if ((semid_one = semgrab(semkey_one)) == -1) {
    /* ERROR: Error when getting id of semaphore one */
    printf("Der erste Semaphor konnte nicht \"gegrabbt\" werden!\n");
    exit(EXIT_FAILURE);
  }
  /* Get ID to second semaphore */
  if ((semid_two = semgrab(semkey_two)) == -1) {
    /* ERROR: Error when getting id of semaphore two */
    printf("Der zweite Semaphor konnte nicht \"gegrabbt\" werden!\n");
    exit(EXIT_FAILURE);
  }
  
  for (aktuellesEl=0;shmptr[aktuellesEl%buffersize]!='\0';aktuellesEl++) {
     if (P(semid_two) == -1) {
       cleanup(shmid, shmptr, semid_one, semid_two);
       exit(EXIT_FAILURE);
     }

     /* Critical section begin */
	   /* write shmptr[aktuellesEl%buffersize] into output file descriptor */
	   if (shmptr[aktuellesEl%buffersize] != '\0') {
	     ch = shmptr[aktuellesEl%buffersize];
	     shmptr[aktuellesEl%buffersize] = '\0';
	     write(STDOUT_FILENO, &ch, 1);
	   }
	   /* Critical section end*/

     if (V(semid_one) == -1) {
       cleanup(shmid, shmptr, semid_one, semid_two);
       exit(EXIT_FAILURE);
     }
  }

  cleanup(shmid, shmptr, semid_one, semid_two);
  return EXIT_SUCCESS;
}
