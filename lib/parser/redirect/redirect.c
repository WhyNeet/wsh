#include "redirect.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

RedirectParseResult parse_redirect(char *raw, size_t n) {
  Redirect *redirect = malloc(sizeof(Redirect));

  size_t offset = 0;
  size_t size = 0;

  char *into;

  while (offset < n && isblank(raw[offset])) {
    offset++;
  }

  while (true) {
    char current_char = raw[offset + size];
    bool is_path_char = (isalnum(current_char) || current_char == '.') &&
                        !isblank(current_char);
    bool is_end = (offset + size) >= n;

    if (!is_path_char || is_end) {
      into = malloc(sizeof(char) * size);
      strncpy(into, raw + offset, size);
      break;
    }

    size++;
  }

  RedirectParseResult result;
  result.redirect = redirect;
  result.size = size + offset;

  return result;
}