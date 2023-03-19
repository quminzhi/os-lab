#include "include/csapp.h"

int main(int argc, char *argv[], char *envp[]) {
  printf("command-line arguments:\n");
  int i = 0;
  while (argv[i] != NULL) {
    printf("argv[%d]: %s\n", i, argv[i]);
    i++;
  }

  printf("environment variables:\n");
  for (int i = 0; envp[i] != NULL; i++) {
    printf("envp[%d]: %s\n", i, envp[i]);
  }

  return 0;
}
