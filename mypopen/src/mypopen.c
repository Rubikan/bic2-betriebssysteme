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
static FILE *myopenFile;

FILE *mypopen(const char *command, const char *type) {
  int pipefd[2];
  pid_t pid;
  FILE *fd = NULL;

  if (strcmp(type,"w") != 0 && strcmp(type,"r") != 0) {
    errno = EINVAL;
    return NULL;
  }
  if (pipe(pipefd) == -1) {
    return NULL;
  }
  if(pid_glob > -2){
    errno=EAGAIN;
    return NULL;
  }
  pid = fork();
  if (pid == 0) {
    /* Child process */
    if (*type == 'w') {
      dup2(pipefd[0], fileno(stdin));
      close(pipefd[0]);

      close(pipefd[1]);
    }
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
  myopenFile=fd;
  /* TODO: Die PID in einer globalen static Variable für pclose speichern. */
  return fd;
}

int mypclose(FILE *stream) {
  pid_t pid = pid_glob;
  pid_t pid_help = 0;
  int status = 0;
  (void) stream;
  pid_glob = -1;
  if(pid == -2 || pid == -1) {
    errno = ECHILD;
    return -1;
  }
  if(myopenFile!=stream){
	  printf("error myopenFile==stream\n");
    errno = EINVAL;
    return -1;
  }
  fclose(stream);
  do{
     pid_help = waitpid(pid, &status,0);  
  }while(pid_help > 0);
  return 1;
}
