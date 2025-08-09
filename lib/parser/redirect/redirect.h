#ifndef LIB_PARSER_REDIRECT_H
#define LIB_PARSER_REDIRECT_H

#include "lib/redirect/redirect.h"
#include <sys/types.h>

typedef struct {
  Redirect *redirect;
  size_t size;
} RedirectParseResult;

RedirectParseResult parse_redirect(char *raw, size_t n);

#endif