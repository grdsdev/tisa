#include "context.h"
#include "util.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CODE_NUM = -1;

enum INSTRUCTION {
  ADD,
  SUB,
  DIV,
  MUL,
  MOV,
  LOADI,
  LOADM,
  STOREM,
  BRZ,
  BRLZ,
  BRNZ,
  IBRZ,
  BRGZ,
  WRITE,
  READ,
  EXIT,
};

enum REG {
  R0,
  R1,
  R2,
  R3,
  R4,
  R5,
  R6,
  R7,
  R8,
  R9,
  R10,
};

int Opcode(const char *mnemonic) {
  if (strcmp(mnemonic, "ADD") == 0)
    return ADD;

  if (strcmp(mnemonic, "SUB") == 0)
    return SUB;

  if (strcmp(mnemonic, "DIV") == 0)
    return DIV;

  if (strcmp(mnemonic, "MUL") == 0)
    return MUL;

  if (strcmp(mnemonic, "MOV") == 0)
    return MOV;

  if (strcmp(mnemonic, "LOADI") == 0)
    return LOADI;

  if (strcmp(mnemonic, "LOADM") == 0)
    return LOADM;

  if (strcmp(mnemonic, "STOREM") == 0)
    return STOREM;

  if (strcmp(mnemonic, "BRZ") == 0)
    return BRZ;

  if (strcmp(mnemonic, "BRLZ") == 0)
    return BRLZ;

  if (strcmp(mnemonic, "BRNZ") == 0)
    return BRNZ;

  if (strcmp(mnemonic, "IBRZ") == 0)
    return IBRZ;

  if (strcmp(mnemonic, "BRGZ") == 0)
    return BRGZ;

  if (strcmp(mnemonic, "WRITE") == 0)
    return WRITE;

  if (strcmp(mnemonic, "READ") == 0)
    return READ;

  if (strcmp(mnemonic, "EXIT") == 0)
    return EXIT;

  return -1;
}

int Decode_reg(const char *str) {
  int reg;
  if (sscanf(str, "r%d", &reg) == 1)
    return reg;
  return -1;
}

int Decode_inst(char *str) {
  char *token, *rx, *ry;
  token = rx = ry = NULL;
  token = strtok(str, " \0");
  int op = Opcode(trim(token));

  instructions[++CODE_NUM].op = op;
  if (op == EXIT)
    return 0;

  rx = strtok(NULL, ",");
  int rx_code = Decode_reg(trim(rx));
  if (op == WRITE || op == READ) {
    instructions[CODE_NUM].rx = rx_code;
    return 0;
  }

  ry = strtok(NULL, "\0");

  int ry_code = Decode_reg(trim(ry));

  if (rx_code == -1)
    rx_code = atoi(rx);

  if (ry_code == -1)
    ry_code = atoi(ry);

  instructions[CODE_NUM].rx = rx_code;
  instructions[CODE_NUM].ry = ry_code;

  return 0;
}

void Load(const char *str) {
  FILE *f = fopen(str, "r");

  char input[255], *token, *rx, *ry;
  token = rx = ry = NULL;
  int res;

  while (!feof(f)) {
    fscanf(f, "%[^\n]", input);
    getc(f);

    res = Decode_inst(input);
    assert(res == 0);
  }

  fclose(f);
}

int Execute(unsigned pc) {
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
    if (registers.r[rx] == 0)
      registers.pc = pc + ry;
    break;
  }

  case BRLZ: {
    if (registers.r[rx] < 0)
      registers.pc = pc + ry;
    break;
  }

  case BRNZ: {
    if (registers.r[rx] != 0)
      registers.pc = pc + ry;
    break;
  }
  case IBRZ: {
    if (registers.r[rx] == 0)
      registers.pc = pc + ram[ry];
    break;
  }

  case BRGZ: {
    if (registers.r[rx] > 0)
      registers.pc = pc + ry;
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

void Dump(void) {
  printf("====== DUMP ======\n\n");
  printf("REGS: [");
  for (int i = 0; i < 10; i++) {
    printf("%ld", registers.r[i]);
    if (i != 9)
      printf(", ");
  }

  printf("]\n");
  printf("PC: %ld\n", registers.pc);
  printf("TICKS: %ld\n", ticks);
  printf("\n\n====== DUMP ======\n");
}

int main(int argc, char **argv) {
  Load(argv[1]);

  while (Execute(registers.pc++) == 0)
    ;

  if (argc == 3)
    if (strcmp(argv[2], "--dump") == 0) {
      Dump();
    }

  return 0;
}