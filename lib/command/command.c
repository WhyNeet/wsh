#include "command.h"
#include <stdlib.h>

void free_command(Command *command) {
  for (int i = 0; i < command->argc; i++) {
    free(command->argv[i]);
  }

  free(command->argv);
}