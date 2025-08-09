#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Pipeline *parse_line(char *line) {
  size_t line_size = strlen(line);

  Pipeline *pipeline = malloc(sizeof(Pipeline));
  PipelineItem *chain = malloc(sizeof(PipelineItem) * 1);
  pipeline->chain = chain;

  size_t chain_current = 0;
  size_t current = 0;

  while (current < line_size) {
    if (current == 0) {
      CommandParseResult command =
          parse_command(line + current, line_size - current);
      current += command.size;
      chain[chain_current].type = PIPELINE_CMD;
      chain[chain_current].item = (void *)command.command;
      chain_current += 1;
    }
  }

  pipeline->size = chain_current;

  return pipeline;
}