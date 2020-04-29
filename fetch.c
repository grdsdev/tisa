#include "fetch.h"

#include <assert.h>
#include <stdio.h>

#include "decode.h"

void load(const char *str) {
  FILE *f = fopen(str, "r");

  char input[255], *token, *rx, *ry;
  token = rx = ry = NULL;
  int res;

  while (!feof(f)) {
    fscanf(f, "%[^\n]", input);
    getc(f);

    res = decode(input);
    assert(res == 0);
  }

  fclose(f);
}
