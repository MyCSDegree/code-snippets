#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#define SIZEOF_PACKET 3
#define SIZEOF_HEADER 2

// char is size 1
#define u8 char

int InitCharBuf(u8 * charbuf, uint n, u8 * pointer) {
  // malloc
  charbuf = malloc( n * sizeof(u8) );

  // if nomem / error
  if (charbuf == NULL)
    return 1;

  // make pointer at charbuf
  pointer = charbuf;

  // finally return 0
  return 0;
}

/* do not forget to call this at end of program */
void deInitCharBuf(u8 * charbuf) {
  if (charbuf != NULL)
    free(charbuf);
}

// TODO: dealith with negatives
int writePacket(u8 * charbuf, u8 * pointer, bool * flip, uint n, int pos) {
  if (pos != -1) {
    ; // deal with writing at specific pos here
    return 0;
  }

  // get first 12 bits alone
  n &= 0xFFF;

  if (~*flip) {
    /* get first 8 bits of x; store in a */
    *pointer  = (n & 0xFFF) >> 4;
    ++pointer;
    /* get last 4 bits of x; shift 4 bits to left */
    *pointer  = ((n & 0xF) << 4);
  } else {
    /* get first 4 bits of y; */
    *pointer |= ((n & 0xffff) >> 8);
    ++pointer;
    /* shift get last 8 bits of y and store in c */
    *pointer  = (n & 0xff);

    // move pointer for next write
    ++pointer;
  }

  // flip flop
  *flip = ~*flip;
  return 0;
}

uint readPacket(uint n) {


  //TODO: while dealing with negatives, we can't do this
  return -1;
}

int main() {
  u8 * charbuf = NULL;
  u8 * pointer = NULL;
  bool    flip = false;

  // init memory!
  if (InitCharBuf(charbuf, 500, pointer)) {
    printf("could not allocate memory!\n");
    return -ENOMEM;
  }

  //writePacket(charbuf, pointer, &flip, n, pos[ = -1])
  writePacket(charbuf, pointer, &flip, 10, -1);
  writePacket(charbuf, pointer, &flip, 12, -1);

  // do not forget to free memory!
  deInitCharBuf(charbuf);
  return 0;
}
