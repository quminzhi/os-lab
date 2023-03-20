#include "include/csapp.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  pid_t pid;

  if ((pid = Fork()) == 0) {
    Pause(); /* wait for a signal to arrive */
    printf("This line should not be printed when receiving a kill signal.\n");
    exit(0);
  }

  Kill(pid, SIGKILL);

  return EXIT_SUCCESS;
}
