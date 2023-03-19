#include "./include/csapp.h"

unsigned int snooze(unsigned int secs) {
  /* return the seconds left */
  unsigned int ret = Sleep(secs);
  printf("Slept for %d of %d secs.\n", secs - ret, secs);
  return ret;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./snooze <secs>\n");
    exit(0);
  }

  unsigned int secs = 0;
  sscanf(argv[1], "%u", &secs);

  unsigned int ret = snooze(secs);
  return 0;
}
