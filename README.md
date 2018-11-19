# TISA
TISA stands for Tiny ISA.

## Bulding and executing

For building the project we're using cmake.
```
mkdir build
cd build
cmake ..
make
```

Then run with:
`./emu ../input.s --dump`


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

## Example

```c
int x = 0;
for (int i = 100; i > 0; i--) {
  for (int k = i; k > 0; k--) {
    x += k;
  }
}
printf("%d\n", x);
```

The `C` code above is translated to:

```assembly
LOADI r1, 0
LOADI r3, 1
LOADI r2, 100
MOV r4, r2
ADD r1, r4
SUB r4, r3
BRNZ r4, -2
SUB r2, r3
BRNZ r2, -5
WRITE r1
EXIT
```
