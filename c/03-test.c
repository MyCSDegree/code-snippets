#include <stdio.h>

int parse (unsigned int n) {
  //printf("%i\n", n & 0xFB);
  return n & 0xFA;
}

int main() {
  unsigned int a = 100;
  unsigned int b = 10;
  unsigned int c = parse(a) + parse(b);
  c = c & 0xFF; // get only 8 bits?

  printf("%i", c);
  return 0;
}
