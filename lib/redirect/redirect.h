#ifndef LIB_REDIRECT_H
#define LIB_REDIRECT_H

typedef struct {
  char *into;
} Redirect;

void free_redirect(Redirect *redirect);

#endif