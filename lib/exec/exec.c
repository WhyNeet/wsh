#include "exec.h"
#include <stdio.h>

void exec_command(Command *command) {
  switch (command->type) {
  case CMD_ECHO:
    for (int i = 1; i < command->argc; i++) {
      printf("%s ", command->argv[i]);
    }
    printf("\n");
    break;
  case CMD_LS:
    break;
  case CMD_EXTERNAL:
    break;
  }
}