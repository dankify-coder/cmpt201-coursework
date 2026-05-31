#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char buff[64];

  while (1) {
    printf("Enter programs to run.\n> ");
    if (fgets(buff, sizeof(buff), stdin) == NULL) {
      break;
    }

    char *program = strtok(buff, "\n");

    pid_t pid = fork();

    if (pid == -1) {
      printf("Fork failed\n");
      exit(1);
    } else if (pid == 0) {
      execl(program, program, (char *)NULL);
      printf("Exec failure\n");
      exit(1);
    } else {
      waitpid(pid, NULL, 0);
    }
  }

  return 0;
}
