#include <iostream>
#include <cmath>
#include <cstring>

#define ll long long

/**
 *  arr: primes arr
 *    a: number to mark multiples of
 *    u: upper limit
 *    l: lower limit
 */
void markMultiples (bool * arr, int a, ll int u, ll int l) {
  // l - (l % a) : rounds down to nearest multiple of a
  ll int numInit =  l + (((l % a) == 0) ? 0 : (a - (l%a)));
  if ((numInit - l + a) == numInit) numInit += a;
  if (l == 1) numInit += a;

  for(ll int num = numInit; num <= u; num += a) {
    //std::cout << num - l << ": " << num << std::endl;
    arr[ num - l ] = 1;
  }
  //std::cout << "-----------------" << std::endl;
}

bool * seive(ll int u, ll int l) {
  bool * arr = new bool[(u - l + 1)];
  memset(arr, 0, sizeof(arr));

  int u_l = (int)ceil(sqrt(u)) + 1;

  if (l == 1)
    arr[0] = 1;

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
  int n;
  std::cin >> n;
  bool *e_seive = NULL;
  for (unsigned i = 0; i < n; i++) {
    ll int a[2];
    std::cin >> a[0] >> a[1];
    e_seive = seive(a[1], a[0]);

    for (int j = 0; j < (a[1] - a[0] + 1); j++) {
      if (e_seive[j] == 0)
        std::cout << j + a[0] << std::endl;
    }
    std::cout << std::endl;

    delete[] e_seive;
  }
  return 0;
}
