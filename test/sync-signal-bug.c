#include "include/csapp.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/*!
 * @brief BUG
 *
 * the child process may terminate before being added to the job queue.
 *
 * In this case, deleteJob(pid) deletes a job does not exist. addJob(pid) 
 * adds a job terminated and it will not be terminated by handler ever.
 *
 * That is for a child process, it terminated before being added to the 
 * list and sent a SIGCHLD signal to parent process when it is blocked.
 *
 * BAD BAD BAD.
 *
 * parent: fork and block ->                            addjob ->
 *
 * child:                    execve and send SIGCHLD ->
 *                                    (may be ignored), become zombie if so
 *
 * => synchronize 
 */

volatile sig_atomic_t count;

void initJobs() {
  count = 0;
};

void addJob(pid_t pid) {
  count++;
};

void deleteJob(pid_t pid) {
  count--;
};

void chld_handler(int sig) {
  int olderrno = errno;
  sigset_t mask_all, prev_all;
  pid_t pid;

  Sigfillset(&mask_all);
  while ((pid = waitpid(-1, NULL, 0)) > 0) {
    // reap a zombie child
    Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
    deleteJob(pid);
    Sigprocmask(SIG_SETMASK, &prev_all, NULL);
  }

  if (errno != ECHILD) {
    Sio_error("waitpid error");
  }

  errno = olderrno;
}

int main(int argc, char *argv[]) {
  pid_t pid;
  sigset_t mask_all, prev_all; /* lock-like */

  Sigfillset(&mask_all);
  Signal(SIGCHLD, chld_handler);
  initJobs(); /* jobs are global variable that may changed in handler */

  while (1) {
    if ((pid = Fork()) == 0) {
      Execve("/bin/date", argv, NULL); /* child process */
    }

    // block all signals
    Sigprocmask(SIG_BLOCK, &mask_all, &prev_all); /* parent process */
    addJob(pid);
    // restore signals
    Sigprocmask(SIG_SETMASK, &prev_all, NULL);
  }

  return EXIT_SUCCESS;
}
