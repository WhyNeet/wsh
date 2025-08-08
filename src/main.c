#include "lib/command/command.h"
#include "lib/exec/exec.h"
#include "lib/input/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  InputBuffer *input_buffer = new_input_buffer();

  while (1) {
    printf("wsh> ");
    readline(input_buffer);
    Command *command = parse_command(input_buffer->buffer);
    exec_command(command);
  }

  close_input_buffer(input_buffer);
}
