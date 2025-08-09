#include "exec.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void exec_echo(Command *cmd) {
  for (int i = 1; i < cmd->argc; i++) {
    printf("%s ", cmd->argv[i]);
  }
  printf("\n");
}

void exec_ls(Command *cmd) {
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));
  DIR *d = opendir(cwd);
  struct dirent *dir;

  while ((dir = readdir(d)) != NULL) {
    printf("%s\n", dir->d_name);
  }
}

void exec_external(Command *cmd) {
  char *file = cmd->argv[0];
  pid_t pid = fork();
  if (pid == 0) {
    execvp(file, cmd->argv);
    perror(cmd->argv[0]);
    exit(1);
  } else if (pid > 0) {
    int status;
    waitpid(pid, &status, 0);
  } else {
    perror("fork");
  }
}

void exec_cd(Command *cmd) {
  if (cmd->argc < 2) {
    fprintf(stderr, "cd: missing argument\n");
    return;
  }

  if (chdir(cmd->argv[1]) != 0)
    perror("cd");
}

void exec_pwd(Command *cmd) {
  if (cmd->argc > 1) {
    fprintf(stderr, "pwd: too many arguments\n");
    return;
  }
  char path[PATH_MAX];
  getcwd(path, sizeof(path));
  printf("%s\n", path);
}

void exec_command(Command *cmd) {
  switch (cmd->type) {
  case CMD_EXTERNAL:
    exec_external(cmd);
    break;
  case CMD_EXIT:
    exit(0);
    break;
  case CMD_TIME:
    printf("not yet implemented\n");
    break;
  case CMD_CD:
    exec_cd(cmd);
    break;
  case CMD_PWD:
    exec_pwd(cmd);
  }
}

void exec_pipeline(Pipeline *pipeline) {
  PipelineItem *chain = pipeline->chain;
  for (int i = 0; i < pipeline->size; i++) {
    switch (chain[i].type) {
    case PIPELINE_CMD:
      exec_command(chain[i].item);
      break;
    case PIPELINE_PIPE:
      printf("pipe: not yet implemented\n");
      break;
    case PIPELINE_STDOUT_REDIRECT:
      printf("stdout redirect: not yet implemented\n");
      break;
    }
  }
}