#include "include/csapp.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief sigint handler
 *
 * @param: sig [int]: the id of signal received
 *
 * @return Nothing.
 */
void sigint_handler(int sig) {
  printf("Caught SIGINT\n");
  exit(0);
}

int main(int argc, char *argv[])
{
  /* install a signal handler */
  if (signal(SIGINT, sigint_handler) == SIG_ERR) {
    unix_error("signal error");
  }

  pause();

  return EXIT_SUCCESS;
}
