#ifndef LIB_PIPELINE_H
#define LIB_PIPELINE_H

#include "lib/command/command.h"
#include <sys/types.h>

typedef struct {
  char *into;
} Redirect;

typedef enum {
  PIPELINE_CMD,
  PIPELINE_PIPE,
  PIPELINE_STDOUT_REDIRECT
} PipelineItemType;

typedef struct {
  PipelineItemType type;
  void *item;
} PipelineItem;

typedef struct {
  PipelineItem *chain;
  size_t size;
} Pipeline;

#endif