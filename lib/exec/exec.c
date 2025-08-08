#include "exec.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void exec_echo(Command *command) {
  for (int i = 1; i < command->argc; i++) {
    printf("%s ", command->argv[i]);
  }
  printf("\n");
}

void exec_ls(Command *command) {
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));
  DIR *d = opendir(cwd);
  struct dirent *dir;

  while ((dir = readdir(d)) != NULL) {
    printf("%s\n", dir->d_name);
  }
}

void exec_external(Command *command) {
  char *file = command->argv[0];
  pid_t pid = fork();
  if (pid == 0) {
    execvp(file, command->argv);
    perror(command->argv[0]);
    exit(1);
  } else if (pid > 0) {
    int status;
    waitpid(pid, &status, 0);
  } else {
    perror("fork");
  }
}

void exec_command(Command *command) {
  switch (command->type) {
  case CMD_ECHO:
    exec_echo(command);
    break;
  case CMD_LS:
    exec_ls(command);
    break;
  case CMD_EXTERNAL:
    exec_external(command);
    break;
  }
}