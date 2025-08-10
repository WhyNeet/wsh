#include "parser.h"
#include "lib/parser/command/command.h"
#include "lib/parser/redirect/redirect.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

Pipeline *parse_line(char *line) {
  size_t line_size = strlen(line);

  Pipeline *pipeline = malloc(sizeof(Pipeline));
  PipelineItem *chain = malloc(sizeof(PipelineItem) * 1);

  size_t chain_current = 0;
  size_t current = 0;
  size_t chain_capacity = 1;

  while (current < line_size) {
    if (isspace(line[current])) {
      while (isspace(line[current])) {
        current++;
      }

      continue;
    }
    if (chain_current + 1 > chain_capacity) {
      size_t new_size = chain_capacity * 2 + 1;
      chain = realloc(chain, new_size * sizeof(PipelineItem));
      chain_capacity = new_size;
    }

    if (line[current] == '>') {
      current += 1;
      RedirectParseResult redirect =
          parse_redirect(line + current, line_size - current);
      current += redirect.size;
      chain[chain_current].type = PIPELINE_STDOUT_REDIRECT;
      chain[chain_current].item = (void *)redirect.redirect;
      chain_current += 1;
    } else {
      CommandParseResult command =
          parse_command(line + current, line_size - current);
      current += command.size;
      chain[chain_current].type = PIPELINE_CMD;
      chain[chain_current].item = (void *)command.command;
      chain_current += 1;
    }
  }

  pipeline->size = chain_current;
  pipeline->chain = chain;

  return pipeline;
}
