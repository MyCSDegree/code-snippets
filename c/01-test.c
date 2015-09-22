#include <stdio.h>

int main() {
  int a = 0xFFFFFFFF; // (1111)*8

  int b = 0x0FFFFFFF; // (0000)(1111)*7
  int c = 0x7FFFFFFF; // (0111)(1111)*7

  printf("%i %i %u %u\n", a, b, a, b);
  printf("%i %i %u %u\n", a, c, a, c);

  return 0;
}

