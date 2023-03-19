#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void unix_error(char *msg) {
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(0);
}

int main() {
  pid_t pid;
  
  if ((pid = fork()) < 0) {
    unix_error("fork error");
  }

  if (pid == 0) return 0;

  FILE *fd;
  if ((fd = fopen("non-exist.txt", "r")) == NULL) {
    unix_error("fopen error");
  }
  
  return 0;
}
