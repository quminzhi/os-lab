#include "include/csapp.h"
#include <stdio.h>
#include <stdlib.h>

/*!
 * @brief reap experiment
 *
 * parent process create ten child processes and do its things until SIGCHLD
 * is received when it reaps child processes that finishes.
 *
 * assumed SIGCHLD is queued is WRONG, since SIGCHLD pending bit is set means
 * there is one or more child processes finished.
 *
 * | -- parent --> |- handler -| -- parent --> | - handler - | -- parent --> |
 *                  reap 1 & 2                  reap 3, 4 & 5
 *
 *      | child 1 F |
 *      | child 2 F |
 *      | -------- child 3 F ----> |
 *      | -------- child 4 F ----> |
 *      | -------------- child 5 F ----> |
 *                ...
 */

#define N 10
#define MAXBUF_SIZE 100

void chld_handler(int sig) {
  int olderrno = errno; /* protect global errno */

  pid_t pid;

  // bug if:
  // if ((pid = waitpid(-1, NULL, 0)) > 0)
  while ((pid = waitpid(-1, NULL, 0)) > 0) { /* reap all finished child processes */
    Sio_puts("Handler reaped child[pid ");
    Sio_putl((long)pid);
    Sio_puts("]\n");
  }

  // errno == ECHILD when the calling process does not have any unwaited-for
  // children
  if (errno != ECHILD) {
    Sio_error("waitpid error");
  }

  Sio_puts("Finished waiting ...\n");

  Sleep(1);

  errno = olderrno;
}

int main(int argc, char *argv[]) {
  char bufline[MAXBUF_SIZE];
  pid_t pid;

  // install signal handler
  if (signal(SIGCHLD, chld_handler) == SIG_ERR) {
    unix_error("signal error");
  }

  for (int i = 0; i < N; i++) {
    if ((pid = Fork()) == 0) {
      printf("Hello from child[%d] with gpid %d\n", getpid(), getgid());
      exit(0);
    }
  }

  // parent process does not wait for child processes.
  int n;
  if ((n = read(STDIN_FILENO, bufline, sizeof(bufline))) < 0) {
    unix_error("read");
  }

  printf("Parent process is processing input\n");
  while (1)
    ;

  return EXIT_SUCCESS;
}
