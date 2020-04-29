#include "context.h"

#include <stdio.h>

struct registers registers;
long ram[1024];
struct instruction instructions[1024];
unsigned long ticks;

void dump(void) {
  printf("\n====== DUMP ======\n\n");
  printf("REGS: [");
  for (int i = 0; i < 10; i++) {
    printf("%ld", registers.r[i]);
    if (i != 9) printf(", ");
  }

  printf("]\n");
  printf("PC: %ld\n", registers.pc);
  printf("TICKS: %ld\n", ticks);
  printf("\n====== DUMP ======\n");
}