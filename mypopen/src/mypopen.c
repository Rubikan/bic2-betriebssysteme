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

FILE *mypopen(const char *command, const char *type) {
  int pipefd[2];
  pid_t pid;
  FILE *fd = NULL;

  if (*type != 'w' && *type != 'r') {
    errno = EINVAL;
    return NULL;
  }
  if (pipe(pipefd) == -1) {
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
  /* TODO: Die PID in einer globalen static Variable für pclose speichern. */
  return fd;
}

int mypclose(FILE *stream) {
  (void) stream;
  return 1;
}
