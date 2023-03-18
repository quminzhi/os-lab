#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define N 16

void unix_error(char *msg) {
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(0);
}

int main() {
  pid_t pid[N];
  int child_status;

  for (int i = 0; i < N; i++) {
    if ((pid[i] = fork()) < 0) {
      unix_error("fork error");
    }
    // child processes just return 100 + i
    if (pid[i] == 0) exit(100 + i);
  }

  for (int i = 0; i < N; i++) {
    pid_t wpid = waitpid(pid[i], &child_status, 0);
    if (WIFEXITED(child_status)) {
      printf("Child[pid %d] terminated with exit status %d (child_status = %d)\n", wpid, WEXITSTATUS(child_status), child_status);
    } else {
      printf("Child[pid %d] terminated abnormally\n", wpid);
    }
  }

  return 0;
}
