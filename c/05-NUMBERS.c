#include <stdio.h>
int main() {
  /* code begin */
  /*1*/ unsigned int arr[] = {/*hex*/0xAB, /*oct*/0154, /*dec*/123, /*bin*/0b1010};
  /*2*/ unsigned int *p = arr;
  /*3*/ do {
  /*4*/   printf("hex: %03x; oct: %03o; dec: %03u;\n", *p, *p, *p);
  /*5*/ } while (*(++p) != 0x00 /* NULL */);
  /* code end */
  return 0;
}
