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

  if (pipe(pipefd) == -1) {
    /*TODO: Error handling*/
  }
  pid = fork(void);
  if (pid == 0) {
    /*TODO: Child process*/
  } else if (pid > 0) {
    /*TODO: Parent process*/
  } else if (pid < 0) {
    /*TODO: Error handling*/
  }
}

int pclose(FILE *stream) {

}
