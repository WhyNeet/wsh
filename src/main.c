#include "lib/exec/exec.h"
#include "lib/input/input.h"
#include "lib/parser/parser.h"
#include "lib/pipeline/pipeline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  InputBuffer *input_buffer = new_input_buffer();

  while (1) {
    printf("wsh> ");
    readline(input_buffer);
    Pipeline *pipeline = parse_line(input_buffer->buffer);
    exec_pipeline(pipeline);
    free_pipeline(pipeline);
  }

  close_input_buffer(input_buffer);
}
