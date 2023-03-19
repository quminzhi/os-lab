#include "./include/csapp.h"

#define N 16

int main() {
  int child_status;
  pid_t pid;

  for (int i = 0; i < N; i++) {
    if ((pid = Fork()) == 0) {
      /* child process */
      exit(100 + i);
    }
  }

  /**
   * when all of the children have been reaped, the next call to waitpid returns
   * -1 and sets errno to ECHILD
   */
  while ((pid = waitpid(-1, &child_status, 0)) > 0) {
    /* wait return from any child process in the waiting list (set) */
    if (WIFEXITED(child_status)) {
      printf("child[pid %d] terminated normally with exit status = %d\n", pid,
             WEXITSTATUS(child_status));
    } else {
      printf("child[pid %d] terminated abnormally\n", pid);
    }
  }

  /* the only normal termination is if there are no more children */
  if (errno != ECHILD) {
    unix_error("waitpid error");
  }

  exit(0);

  return 0;
}
