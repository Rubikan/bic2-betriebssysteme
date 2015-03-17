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

FILE *popen(const char *command, const char *type) {
  int pipefd[2];
  pid_t pid;

  if (*type != 'w' && *type != 'r') {
    errno = EINVAL;
    return NULL;
  }
  if (pipe(pipefd) == -1) {
    return NULL;
  }
  pid = fork(void);
  if (pid == 0) {
    switch(type) {
      case 'w':
        dup2(pdes[0], fileno(stdin));
        close(pdex[0]);
        break;
      case 'r':
        dup2(pdes[1], fileno(stdout));
        close(pdex[1]);
        break;
    }
    /*TODO: Execute command in child*/
  } else if (pid > 0) {
    /*TODO: Parent process*/
  } else if (pid < 0) {
    return NULL;
  }
}

int pclose(FILE *stream) {

}
