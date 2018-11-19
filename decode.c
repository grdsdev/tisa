#include "decode.h"
#include "context.h"
#include "instructions.h"
#include "registers.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int opcode(const char *mnemonic) {
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

static int decode_reg(const char *str) {
  int Reg;
  if (sscanf(str, "r%d", &Reg) == 1)
    return Reg;
  return -1;
}

int decode(char *str) {
  static int CODE_NUM = -1;

  char *token, *rx, *ry;
  token = rx = ry = NULL;
  token = strtok(str, " \0");
  int op = opcode(trim(token));

  instructions[++CODE_NUM].op = op;
  if (op == EXIT)
    return 0;

  rx = strtok(NULL, ",");
  int rx_code = decode_reg(trim(rx));
  if (op == WRITE || op == READ) {
    instructions[CODE_NUM].rx = rx_code;
    return 0;
  }

  ry = strtok(NULL, "\0");

  int ry_code = decode_reg(trim(ry));

  if (rx_code == -1)
    rx_code = atoi(rx);

  if (ry_code == -1)
    ry_code = atoi(ry);

  instructions[CODE_NUM].rx = rx_code;
  instructions[CODE_NUM].ry = ry_code;

  return 0;
}