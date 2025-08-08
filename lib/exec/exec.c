#include "exec.h"
#include <dirent.h>
#include <stdio.h>
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

void exec_command(Command *command) {
  switch (command->type) {
  case CMD_ECHO:
    exec_echo(command);
    break;
  case CMD_LS:
    exec_ls(command);
    break;
  case CMD_EXTERNAL:
    break;
  }
}