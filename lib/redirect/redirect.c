#include "redirect.h"
#include <stdlib.h>

void free_redirect(Redirect *redirect) { free(redirect->into); }