#include "include/csapp.h"
#include <stdio.h>
#include <stdlib.h>

void int_handler(int sig) { return; }

unsigned int snooze(unsigned int secs) {
  /* return control to sleep and it will execute next inst (return) from sleep
   * state */
  unsigned int rc = Sleep(secs);

  printf("Slept for %d of %d secs.\n", secs - rc, secs);

  return rc; /* return code */
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: ./snooze1 <secs>\n");
    exit(0);
  }

  if (signal(SIGINT, int_handler) == SIG_ERR) {
    unix_error("signal error");
  }

  int secs = atoi(argv[1]);
  snooze(secs);

  return EXIT_SUCCESS;
}
