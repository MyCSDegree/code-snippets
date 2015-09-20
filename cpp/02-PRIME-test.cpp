#include <iostream>
#include <cmath>
#include <cstring>

/**
 *  arr: primes arr
 *    a: number to mark multiples of
 *    u: upper limit
 *    l: lower limit
 */
void markMultiples (bool * arr, int a, int u, int l) {
  // l - (l % a) : rounds down to nearest multiple of a
  int numInit =  l + (((l % a) == 0) ? 0 : (a - (l%a)));
  for(int num = numInit; num <= u; num += a) {
//    std::cout << num - l << ": " << num << std::endl;
    arr[ num - l ] = 1;
  }
  //std::cout << "-----------------" << std::endl;
}

bool * seive(int u, int l) {
  bool * arr = new bool[(u - l + 1)];
  memset(arr, 0, sizeof(arr));

  int u_l = (int)ceil(sqrt(u));

  if (u > 1) {
    for (int i = 1; i < u_l; i++) {
      //if (arr[i] == 0) {
        markMultiples(arr, (i+1), u, l);
      //} // if isprime
    } // for (main loop)
  } // u > 1

  return arr;
}


int main() {

  int l = 5, u = 25;

  bool *e_seive = seive(u, l);
  //std::cout << "===========================" << std::endl;
  for (int j = 0; j < (u - l + 1); j++) {
    if (e_seive[j] == 0)
      std::cout << j + l << std::endl;
  }

  return 0;
}
