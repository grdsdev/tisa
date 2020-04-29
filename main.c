#include <string.h>

#include "context.h"
#include "execute.h"
#include "fetch.h"

int main(int argc, char **argv) {
  load(argv[1]);

  while (execute(registers.pc++) == 0)
    ;

  if (argc == 3)
    if (strcmp(argv[2], "--dump") == 0) dump();

  return 0;
}
