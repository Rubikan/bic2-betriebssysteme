/**
 *
 * @file shared.c
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

/**
 * \brief Prints the usage message for false arguments
 *
 * \return void
 */
void print_usage() {
    printf("Usage: [sender empfaenger] -m num\n");
}

/**
 * \brief Uses getopt to get the buffersize for the ring buffer
 *
 * \return integer Size the ringbuffer should have
 */
int get_buffersize(int argc, char* argv[]) {
  int buffersize;
  int opt;

  while ((opt = getopt(argc, argv, "m:")) != -1) {
    switch(opt) {
      case 'm':
        buffersize = atoi(optarg);
        break;
      default:
        print_usage();
        exit(EXIT_FAILURE);
    }
  }

  return buffersize;
}
