#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <string.h>


/**
 * okay, so we wanna work with just positive int numbers for starters
 * to do that, first off, figure out the max number which can be stored in an
 * integer.
 *
 * for doing that, we need to understand how negative numbers are represented
 * signed-ness and unsigned-ness
 *
 * first bit indicates complementarity(?), and thus signed-ness.
 *
 * for a number of x bits, (2 ^ x) - 1 can be stored
 *
 * but. with hexadecimal numbers, ??? complementarity?
 * max becomes 7 // refer 01-test.c
 *
 * to find the complement of a number n, what is to be doen?
 * ~n + 1
 *
 * thus, if say we need to convert negative numbers, we need to parse it
 * separately
 *
 * ignore it for now? would be the safest option
 *
 * sizeof(int) gives size of int in **bytes**
 * multiply it by 8 and
 *   divide by 4 to get max chr of hex
 *   divide by 3 to get max chr of oct (???)
 *   divide by 2 to get max chr of ???
 *   divide by 1 to get max chr of binary
 *
 * thus, for any given compiler, we will have:
 * int_size  = sizeof(int) * 8
 * uint_size = sizeof(unsigned int) * 8
 *
 * max chr of hex: uint_size / 4
 * max chr of oct: floor(uint_size / 3) (or) (uint_size - 2) / 3 (why x-2? 8%3)
 * max chr of ???: forget this
 * max chr of bin: uint_size
 *
 *
 * NOTE: build with -lm to use pow, floor, define #BUILD_LM in the case
 */

// assume sizeof will ALWAYS return number of bytes in int
#define int_size  sizeof(unsigned int) * 8
#define uint_size sizeof(unsigned int) * 8

#define max_hex (int)uint_size / 4
#define max_oct (int)(uint_size - 2) / 3
#define max_bin (int)uint_size

//#define BUILD_LM

void get_input(char*input, int limit) {
#ifdef BUILD_LM
  int sizeof_limit = (int) log10(limit) + 1;
#else
  int sizeof_limit = 0;
  int limit_iter   = limit;
  while (limit_iter > 0) {
    ++sizeof_limit;
    limit_iter /= 10;
  }
#endif // BUILD_LM
  char sequence[sizeof_limit+2]; // +2 for? '%' + n + 's'
  sprintf(sequence, "%c%is", 37, limit);
  scanf(sequence, input);
  /* TODO: garbage collection done by os? */
  /* or delete stuff here */
}

void parse_binary(char* str, unsigned int *n) {
  int count = 0;
  int iter  = strlen(str);
  int digit = 0;
  while (iter > 0) {
    digit = (int)str[iter-1] - '0';
    if (digit) {// if 1 calc power
#ifndef BUILD_LM
      int i = 0;
      int power = 1;
      for (i = 0; i < count; i++)
        power = power * 2;
      *n = *n + power;
#else
      *n += (int)pow(2, count);
#endif
    } // if(digit)

    count += 1;
    iter  -= 1;
  } // while
} // parse_binary

int check_hex(char *str) {
  int iter  = strlen(str);
  while (iter > 0) {
    //TODO: implicit declaration of function, tofix.
    if (toupper(str[iter-1]) < '0' || toupper(str[iter-1]) > 'F')
      return 0;

    iter -= 1;
  } // while
  return 1;
} // check_hex

/**
 * hex_table, probably the fastest way to do this.
 * A = 65
 * 9 = 57
 *
 */
const int hex_table[] = {
/*  48, 49, 50, 51, 52, 53, 54, 55, 56, 57 */
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
/*  58, 59, 60, 61, 62, 63, 64, 65, 66, 67 */
    -1, -1, -1, -1, -1, -1, -1, 10, 11, 12,
/*  68, 69, 70, 61, 62, 63, 64, 65, 66, 67 */
    13, 14, 15
};

void parse_hex(char *str, unsigned int *n) {
  int iter  = strlen(str);
  int count = 0;
  int digit = 0;
  while (iter > 0) {
    digit = hex_table[toupper(str[iter-1]) - '0'];
#ifndef BUILD_LM
    int i = 0;
    int power = 1;
    for (i = 0; i < count; i++)
      power = power * 16;
    *n = *n + (digit * power);
#else
    *n += digit * (int)pow(16, count);
#endif

    count += 1;
    iter  -= 1;
  } // while
} // parse_hex

char *strrev(char *str) {
  char *p1, *p2;

  if (! str || ! *str)
    return str;
  for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
    *p1 ^= *p2;
    *p2 ^= *p1;
    *p1 ^= *p2;
  }
  return str;
}

const char hex_str[] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  'A', 'B', 'C', 'D', 'E', 'F'
};
void format_base(int n, char* str, int base) {
  int pos = 0;
  int temp = 0;
  while(n != 0) {
    temp = n % base;
    str[pos] = hex_str[temp];
    n /= base;
    pos += 1;
  }
  str[pos] = '\0';
  str = strrev(str);
}

void show_number(unsigned int *n, char* str) {
  printf("decimal: %u\n", *n);
  format_base(*n, str, 16); // reuse str to show output?
  printf("hex    : %s\n", str);
  format_base(*n, str,  2); // reuse str to show output?
  printf("bin    : %s\n", str);
}

int main() {
  char          str[uint_size+1]; // terminating null adds a char
  unsigned int  parsed_input = 0;
  /* input in binary */
  printf("binary input: ");
  get_input(str, max_bin);
  parse_binary(str, &parsed_input);
  show_number(&parsed_input, str);
  parsed_input = 0;
  memset(str, 0, sizeof(str));
  printf("--------------\n");


  /* input in hex */
  printf("hex input: ");
  get_input(str, max_hex);
  if (!check_hex(str)) {
    printf("invalid hex input!\n");
  } else {
    parse_hex(str, &parsed_input);
    show_number(&parsed_input, str);
  }
  parsed_input = 0;
  memset(str, 0, sizeof(str));
  printf("--------------\n");


  /* input in dec */
  printf("decimal input: ");
  scanf("%u", &parsed_input);
  show_number(&parsed_input, str);
  parsed_input = 0;
  memset(str, 0, sizeof(str));
  printf("--------------\n");

  return 0;
}
