#ifndef LIB_PARSER_CMD_H
#define LIB_PARSER_CMD_H

#include "lib/command/command.h"
#include <sys/types.h>

typedef struct {
  Command *command;
  size_t size;
} CommandParseResult;

CommandParseResult parse_command(char *raw, size_t n);

#endif