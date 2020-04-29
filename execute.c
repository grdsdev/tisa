#include "execute.h"

#include <stdio.h>

#include "context.h"
#include "instructions.h"
#include "registers.h"

int execute(unsigned pc) {
  ticks++;

  int op = instructions[pc].op;
  int rx = instructions[pc].rx;
  int ry = instructions[pc].ry;

  switch (op) {
    case ADD: {
      registers.r[rx] = registers.r[rx] + registers.r[ry];
      break;
    }

    case SUB: {
      registers.r[rx] = registers.r[rx] - registers.r[ry];
      break;
    }

    case DIV: {
      registers.r[rx] = registers.r[rx] / registers.r[ry];
      break;
    }

    case MUL: {
      registers.r[rx] = registers.r[rx] * registers.r[ry];
      break;
    }

    case MOV: {
      registers.r[rx] = registers.r[ry];
      break;
    }

    case LOADI: {
      registers.r[rx] = ry;
      break;
    }

    case LOADM: {
      registers.r[rx] = ram[ry];
      break;
    }

    case STOREM: {
      ram[ry] = registers.r[rx];
      break;
    }

    case BRZ: {
      if (registers.r[rx] == 0) registers.pc = pc + ry;
      break;
    }

    case BRLZ: {
      if (registers.r[rx] < 0) registers.pc = pc + ry;
      break;
    }

    case BRNZ: {
      if (registers.r[rx] != 0) registers.pc = pc + ry;
      break;
    }
    case IBRZ: {
      if (registers.r[rx] == 0) registers.pc = pc + ram[ry];
      break;
    }

    case BRGZ: {
      if (registers.r[rx] > 0) registers.pc = pc + ry;
      break;
    }
    case WRITE: {
      printf("%ld\n", registers.r[rx]);
      break;
    }

    case READ: {
      scanf("%ld", &registers.r[rx]);
      break;
    }

    case EXIT: {
      return 1;
    }
  }

  return 0;
}