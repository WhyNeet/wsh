#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readline(void *src) {
  char buffer[10];
  char *input = 0;
  size_t cur_len = 0;
  size_t cur_max = 0;
  while (fgets(buffer, sizeof(buffer), src) != NULL) {
    size_t buf_len = strlen(buffer);

    if (cur_len + buf_len + 1 > cur_max) {
      size_t new_len = cur_max * 2 + 1;
      if (buf_len + 1 > new_len)
        new_len = buf_len + 1;
      char *extra = realloc(input, new_len);
      if (extra == 0)
        break;
      input = extra;
      cur_max = new_len;
    }

    strcpy(input + cur_len, buffer);
    cur_len += buf_len;
    if (buffer[buf_len - 1] == '\n') {
      break;
    }
  }

  return input;
}
