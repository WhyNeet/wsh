#include "pipeline.h"
#include "lib/command/command.h"
#include "lib/redirect/redirect.h"
#include <stdio.h>
#include <stdlib.h>

void free_pipeline(Pipeline *pipeline) {
  for (int i = 0; i < pipeline->size; i++) {
    void *item = pipeline->chain[i].item;
    switch (pipeline->chain[i].type) {
    case PIPELINE_CMD:
      free_command(item);
      break;
    case PIPELINE_STDOUT_REDIRECT:
      free_redirect(item);
      break;
    case PIPELINE_PIPE:
      printf("free_pipe: not yet implemented\n");
      break;
    }
  }

  free(pipeline);
}