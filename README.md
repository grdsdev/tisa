# toy-emulator
Tiny emulator for a toy ISA

## Bulding and executing

```
cc -O3 main.c context.c -o emu
./emu input.s --dump
```


## Supported instructions

- ADD rx, ry // rx = rx + ry
- SUB rx, ry
- DIV rx, ry
- MUL rx, ry
- BRZ rx, DES // PC += DES se rx = 0
- BRNZ rx, DES // PC += DES se rx != 0
- BRLZ rx, DES // PC += DES se rx < 0
- BRGZ rx, DES // PC += DES se rx > 0
- IBRZ rx, ADR // PC = MEM(ADR) se rx = 0
- MOV rx, ry // rx = ry
- LOADM rx, ADR // rx = MEM(ADR)
- STOREM rx, ADR // MEM(ADR) = rx
- LOADI rx, VAL // rx = VAL
- WRITE rx // printf(“%d\n”, rx)
- READ rx // scanf(“%d”, rx)
- EXIT // exit(0)
