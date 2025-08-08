#include "command.h"
#include <stdlib.h>
#include <string.h>

Command *parse_command(char *raw) {
  Command *command = (Command *)malloc(sizeof(Command));

  char *cmd_type_s = strtok(raw, " ");

  CommandType cmd_type = CMD_EXTERNAL;
  if (strcmp(cmd_type_s, "time") == 0)
    cmd_type = CMD_TIME;

  command->type = cmd_type;

  char **argv = (char **)malloc(sizeof(char *) * 2);
  argv[0] = strdup(cmd_type_s);
  size_t argc = 1;
  size_t capacity = 2;
  char *cur_token = strtok(NULL, " ");

  while (cur_token != NULL) {
    if (argc + 1 + 1 > capacity) {
      size_t new_len = capacity * 2 + 1;
      argv = realloc(argv, new_len * sizeof(char *));
      capacity = new_len;
    }
    argv[argc] = strdup(cur_token);
    argc += 1;
    cur_token = strtok(NULL, " ");
  }

  argv[argc] = NULL;
  command->argv = argv;
  command->argc = argc;

  return command;
}

void free_command(Command *command) {
  for (int i = 0; i < command->argc; i++) {
    free(command->argv[i]);
  }

  free(command->argv);
}