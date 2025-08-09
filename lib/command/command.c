#include "command.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CommandParseResult parse_command(char *raw, size_t n) {
  Command *command = (Command *)malloc(sizeof(Command));

  char *cmd_type_s = strtok(raw, " ");

  CommandType cmd_type = CMD_EXTERNAL;
  if (strcmp(cmd_type_s, "exit") == 0)
    cmd_type = CMD_EXIT;
  else if (strcmp(cmd_type_s, "time") == 0)
    cmd_type = CMD_TIME;
  else if (strcmp(cmd_type_s, "cd") == 0)
    cmd_type = CMD_CD;
  else if (strcmp(cmd_type_s, "pwd") == 0)
    cmd_type = CMD_PWD;

  command->type = cmd_type;

  char **argv = (char **)malloc(sizeof(char *) * 2);
  argv[0] = strdup(cmd_type_s);
  size_t argc = 1;
  size_t capacity = 2;

  int start = strlen(cmd_type_s) + 1;
  int end = start;

  while (true) {
    char current_char = raw[end];

    bool is_delim = current_char == ' ';
    bool is_special =
        current_char == '>' || current_char == '<' || current_char == '|';
    bool is_end = end >= n;

    if (is_delim || is_special || is_end) {
      if ((is_special || is_end) && start == end)
        break;

      if (argc + 1 + 1 > capacity) {
        size_t new_len = capacity * 2 + 1;
        argv = realloc(argv, new_len * sizeof(char *));
        capacity = new_len;
      }
      size_t token_size = end - start;
      char *cur_token = malloc(token_size * sizeof(char *) + 1);
      strncpy(cur_token, raw + start, token_size);
      cur_token[token_size] = '\0';
      argv[argc] = cur_token;
      argc += 1;

      start = ++end;
      if (is_special || is_end)
        break;
      continue;
    }

    end++;
  }

  argv[argc] = NULL;
  command->argv = argv;
  command->argc = argc;

  CommandParseResult result;
  result.command = command;
  result.size = end;

  return result;
}

void free_command(Command *command) {
  for (int i = 0; i < command->argc; i++) {
    free(command->argv[i]);
  }

  free(command->argv);
}