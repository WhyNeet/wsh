#include "exec.h"
#include <dirent.h>
#include <fcntl.h>
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

void exec_command(Command *cmd, Redirect **stdout_redirects,
                  size_t num_redirects) {
  int *fds = malloc(sizeof(int) * num_redirects);
  int initial_stdout = dup(STDOUT_FILENO);
  int pipe_fd[2];
  if (initial_stdout == -1) {
    perror("dup");
    return;
  }

  if (num_redirects > 0) {
    // open all files
    for (int i = 0; i < num_redirects; i++) {
      fds[i] =
          open(stdout_redirects[i]->into, O_WRONLY | O_TRUNC | O_CREAT, 0644);
      if (fds[i] == -1) {
        perror("fopen");
        close(initial_stdout);
        return;
      }
    }

    // create a pipe to capture stdout
    if (pipe(pipe_fd) == -1) {
      perror("pipe");
      for (int i = 0; i < num_redirects; i++) {
        close(fds[i]);
      }
      close(initial_stdout);
      free(fds);
      return;
    }

    pid_t tee_pid = fork();
    switch (tee_pid) {
    case -1:
      perror("fork");
      for (int i = 0; i < num_redirects; i++) {
        close(fds[i]);
      }
      close(initial_stdout);
      close(pipe_fd[0]);
      close(pipe_fd[1]);
      free(fds);
      return;
    case 0:
      // child process will write output to files
      // child process does not need to write
      close(pipe_fd[1]);
      char buffer[4096];
      ssize_t n;
      while ((n = read(pipe_fd[0], buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < num_redirects; i++) {
          write(fds[i], buffer, n);
        }
      }
      close(pipe_fd[0]);
      for (int i = 0; i < num_redirects; i++) {
        close(fds[i]);
      }
      exit(0);
    default:
      // parent process will redirect stdout to a pipe
      close(pipe_fd[0]);
      dup2(pipe_fd[1], STDOUT_FILENO);
      break;
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

  if (num_redirects > 0) {
    fflush(stdout);
    close(pipe_fd[1]);
    dup2(initial_stdout, STDOUT_FILENO);
    close(initial_stdout);
    int status;
    waitpid(-1, &status, 0);
  }
}

void exec_pipeline(Pipeline *pipeline) {
  PipelineItem *chain = pipeline->chain;
  Command *command = chain[0].item;
  Redirect **redirects = malloc(sizeof(Redirect *));

  size_t redirects_capacity = 1;
  size_t num_redirects = 0;

  for (int i = 1; i < pipeline->size; i++) {
    switch (chain[i].type) {
    case PIPELINE_CMD:
      exit(1);
    case PIPELINE_PIPE:
      printf("pipe: not yet implemented\n");
      break;
    case PIPELINE_STDOUT_REDIRECT:
      if (num_redirects + 1 > redirects_capacity) {
        size_t new_size = redirects_capacity * 2 + 1;
        redirects = realloc(redirects, new_size * sizeof(Redirect *));
        redirects_capacity = new_size;
      }
      redirects[num_redirects++] = chain[i].item;
      break;
    }
  }

  exec_command(command, redirects, num_redirects);
}