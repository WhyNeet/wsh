#include "command.h"
#include <stdlib.h>
#include <string.h>

Command *parse_command(char *raw) {
  Command *command = (Command *)malloc(sizeof(Command));

  char *cmd_type_s = strtok(raw, " ");

  CommandType cmd_type = CMD_EXTERNAL;
  if (strcmp(cmd_type_s, "echo") == 0)
    cmd_type = CMD_ECHO;
  else if (strcmp(cmd_type_s, "ls") == 0)
    cmd_type = CMD_LS;

  command->type = cmd_type;

  char **argv = NULL;
  size_t max_len = 0;
  size_t argc = 0;
  char *cur_token = strtok(NULL, " ");

  while (cur_token != NULL) {
    if (argc + 1 + 1 > max_len) {
      size_t new_len = max_len * 2 + 1;
      argv = realloc(argv, new_len * sizeof(char *));
      cur_token = strtok(NULL, " ");
    }
    argv[argc] = cur_token;
  }

  command->argv = argv;
  command->argc = argc;

  return command;
}