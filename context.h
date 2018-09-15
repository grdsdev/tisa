#pragma once

struct registers {
  long r[10];
  long pc;
} extern registers;

extern long ram[1024];

struct instruction {
  int op;
  long rx, ry;
} extern instructions[1024];

extern unsigned long ticks;