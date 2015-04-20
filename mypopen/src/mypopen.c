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

FILE *mypopen(const char *command, const char *type) {
  int pipefd[2];
  pid_t pid;
  FILE *fd = NULL;
/*vergleichen der eingabe mit den erlaubten Parametern w und r*/
  if (strcmp(type,"w") != 0 && strcmp(type,"r") != 0) {
    errno = EINVAL;
    return NULL;
  }
  /*öffnen einer Pipe*/ 
  if (pipe(pipefd) == -1) {
    return NULL;
  }
  /*vergleich der Pipe ID*/  
  if (pid_glob > -1) {
    errno = EAGAIN;
    return NULL;
  }
  /*öffnen eines Kindprozesses*/  
  pid = fork();
  if (pid == 0) {
    /* Child process */
    /*Schliessen der Pipeenden die für den write Befehl im Kind Prozess nicht benötigt werden*/	
    if (*type == 'w') {
      dup2(pipefd[0], fileno(stdin));
      close(pipefd[0]);

      close(pipefd[1]);
    }
    /*Schliessen der Pipeenden die für den read Befehl im Kind Prozess nicht benötigt werden*/
    if (*type == 'r') {
      dup2(pipefd[1], fileno(stdout));
      close(pipefd[1]);

      close(pipefd[0]);
    }
    execl(SHELL, SHELL, "-c", command, NULL);

  } else if (pid > 0) {
    /* Parent process */
    if (*type == 'w') {
      fd = fdopen(pipefd[1], type);
      close(pipefd[0]);
    }
    if (*type == 'r') {
      fd = fdopen(pipefd[0], type);
      close(pipefd[1]);
    }

  } else if (pid < 0) {
    /* Error while forking */
    return NULL;
  }
  pid_glob = pid;
  /* TODO: Die PID in einer globalen static Variable für pclose speichern. */
  return fd;
}
/*Schliessen des Kindprozesses*/
int mypclose(FILE *stream) {
  pid_t pid = pid_glob;
  pid_t pid_help = 0;
  int status = 0;
  (void) stream;
  pid_glob = -1;
   /*hier wird überprüft ob überhaupt ein kindprozess existiert*/ 
  if(pid == -2 || pid == -1) {
    errno = ECHILD;
    return -1;
  }
  printf("pid: %d\n", pid);
  pid_help = getpid();
  printf("pid_help: %d\n", pid_help);
  /*Hier wird auf ungültige argumente überprüft*/  
  if(pid_help != pid){
    errno = EINVAL;
    return -1;
  }
  pid_help = waitpid(-1, &status,0);
  if(pid_help > 0){
    return -1;
  }
  fclose(stream);
  return 1;
}
