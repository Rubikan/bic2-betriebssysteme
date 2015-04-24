/**
 *
 * @file mypopen.c
 * Betriebssysteme Betriebssysteme mypopen File.
 * Beispiel 2
 *
 * @author Andreas Rubik <andreas.rubik@technikum-wien.at>
 * @author Anna Glock <ic14b070@technikum-wien.at>
 * @author Anna Huka <ic14b043@technikum-wien.at>
 *
 * @version 1.0
 * @date 2015/03/13
 *
 */

#include "mypopen.h"

#define SHELL "/bin/sh"

static pid_t pid_glob = -2;
static FILE *myopenFile = NULL;

/**
* öffnet einen Prozess indem eine Pipe erstellt wird, und öffnet einen Kind Prozess
* 
 * mit command wählt man die Funktion aus die im Kind Prozess ausgeführt werden soll
 * 
 * mit type wird festgelegt wie der Kind Prozess ausgeführt werden soll, entweder 
 * mit ("w") für schreiben oder mit ("r") für lesen
 * 
 * zurückgegeben wird bei erfolgreicher Ausführung der File descriptor, bei Fehlern wird NULL zurückgegeben
 */
FILE *mypopen(const char *command, const char *type) {
  int pipefd[2];
  pid_t pid;
  FILE *fd = NULL;
  /* Überprüfen ob der mitgegebene Type gültig ist */
  if (strncmp(type,"w", 1) != 0 && strncmp(type,"r", 1) != 0) {
    errno = EINVAL;
    return NULL;
  }
  /* öffnen einer Pipe */
  if (pipe(pipefd) == -1) {
    return NULL;
  }
  /* Sicherstellen, dass mypopen nur 1 mal gleichzeitig aufgerufen werden kann */
  if (myopenFile != NULL) {
    errno = EAGAIN;
    return NULL;
  }
  pid = fork();
  if (pid == 0) {
    /* Kindprozess*/
    /*Schliessen der für den "write" Befehl nicht nötigen Enden der Pipe */
    if (*type == 'w') {
      dup2(pipefd[0], fileno(stdin));
      close(pipefd[0]);

      close(pipefd[1]);
    }
    /* Schliessen der für den "read" Befehl nicht nötigen Enden der Pipe */
    if (*type == 'r') {
      dup2(pipefd[1], fileno(stdout));
      close(pipefd[1]);

      close(pipefd[0]);
    }
    execl(SHELL, SHELL, "-c", command, NULL);
    return NULL;

  } else if (pid > 0) {
    /* Elternprozess */
    if (*type == 'w') {
      fd = fdopen(pipefd[1], type);
      close(pipefd[0]);
    }
    if (*type == 'r') {
      fd = fdopen(pipefd[0], type);
      close(pipefd[1]);
    }
    myopenFile = fd;

  } else if (pid < 0) {
    /* Fehler beim Erstellen des Kindprozesses*/
    errno = EAGAIN;
    close(pipefd[1]);
    close(pipefd[0]);
	  myopenFile=NULL;
    return NULL;
  }
  pid_glob = pid;
  return fd;
}

/**
 * Wartet bis der Prozess beendet wird und gibt den Exit Status zurück
 * 
 * Parameter stream ist ein File descriptor des Prozesses der geschlossen werden soll
 * 
 * gibt 1 bei Erfolg zurück und -1 bei einem Fehler
 */

int mypclose(FILE *stream) {
  pid_t pid_help = 0;
  int status = 0;
  (void) stream;
   /* Überprüfung ob ein Kindprozess existiert */
  if (myopenFile == NULL) {
    errno = ECHILD;
    return -1;
  }
  /* Hier wird auf ungültige Argumente überprüft */
  if (myopenFile!=stream) {
    errno = EINVAL;
    return -1;
  }
  fclose(stream);
  do {
     pid_help = waitpid(pid_glob, &status,0);
  } while(pid_help > 0);
  if (WIFEXITED(status) != 0){
	  return WEXITSTATUS(status);
  }
  if (!WIFEXITED(status) && WEXITSTATUS(status) == 0) {
    errno = ECHILD;
    return -1;
  }
  pid_glob = -1;
  myopenFile = NULL;
  return 1;
}
