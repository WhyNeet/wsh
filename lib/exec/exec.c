#include "exec.h"
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
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
  execvp(file, cmd->argv);
  perror(cmd->argv[0]);
  exit(1);
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

void exec_command(Command *cmd, Redirect *stdout_redirect) {
  int initial_stdout = -1;
  int fd = -1;
  if (stdout_redirect != NULL) {
    initial_stdout = dup(STDOUT_FILENO);
    if (initial_stdout == -1) {
      perror("dup");
      return;
    }

    fd = open(stdout_redirect->into, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd == -1) {
      perror("fopen");
      close(initial_stdout);
      return;
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
      perror("dup2");
      close(fd);
      close(initial_stdout);
      return;
    }
  }

  switch (cmd->type) {
  case CMD_EXTERNAL: {
    pid_t pid = fork();
    switch (pid) {
    case -1:
      perror("fork");
      break;
    case 0:
      exec_external(cmd);

      exit(0);
    default: {
      int status = 0;
      waitpid(pid, &status, 0);
      break;
    }
    }
    break;
  }
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

  if (stdout_redirect != NULL) {
    fflush(stdout);
    dup2(initial_stdout, STDOUT_FILENO);
    close(initial_stdout);
    close(fd);
  }
}

void exec_pipeline(Pipeline *pipeline) {
  PipelineItem *chain = pipeline->chain;
  Command *command = chain[0].item;
  Redirect *redirect = NULL;

  if (pipeline->size > 1) {
    switch (chain[1].type) {
    case PIPELINE_CMD:
      exit(1);
    case PIPELINE_PIPE:
      printf("pipe: not yet implemented\n");
      break;
    case PIPELINE_STDOUT_REDIRECT:
      redirect = chain[1].item;
      break;
    }
  }

  exec_command(command, redirect);
}