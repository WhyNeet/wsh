#include "lib/input/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  while (1) {
    printf("wsh> ");
    char *input = readline(stdin);
    printf("%s", input);
    free(input);
  }
}
