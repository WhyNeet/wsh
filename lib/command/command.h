#ifndef LIB_COMMAND_H
#define LIB_COMMAND_H

#include <stddef.h>

typedef enum { CMD_ECHO, CMD_LS, CMD_EXTERNAL } CommandType;

typedef struct {
  CommandType type;
  char **argv;
  size_t argc;
} Command;

Command *parse_command(char *raw);
void free_command(Command *command);

#endif