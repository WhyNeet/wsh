#ifndef LIB_COMMAND_H
#define LIB_COMMAND_H

#include <stddef.h>

typedef enum { CMD_EXIT, CMD_PWD, CMD_CD, CMD_TIME, CMD_EXTERNAL } CommandType;

typedef struct {
  CommandType type;
  char **argv;
  size_t argc;
} Command;

typedef struct {
  Command *command;
  size_t size;
} CommandParseResult;

CommandParseResult parse_command(char *raw, size_t n);
void free_command(Command *command);

#endif