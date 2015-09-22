#include <iostream>
#include <cmath>
#include <cstring>

#define ll long long
#define MAX 1000000000

bool primes[MAX];

/**
 *  arr: primes arr
 *    a: number to mark multiples of
 *    u: upper limit
 *    l: lower limit
 */
void markMultiples (int a, ll int u, ll int l) {
  // l - (l % a) : rounds down to nearest multiple of a
  ll int numInit =  l + (((l % a) == 0) ? 0 : (a - (l%a)));
  if ((numInit - l + a) == numInit) numInit += a;
  if (l == 1) numInit += a;

  for(ll int num = numInit; num <= u; num += a) {
    //std::cout << num - l << ": " << num << std::endl;
    primes[ num - l ] = 1;
  }
  //std::cout << "-----------------" << std::endl;
}

void seive(ll int u, ll int l) {
  int u_l = (int)ceil(sqrt(u)) + 1;

  if (l == 1)
    primes[0] = 1;

  if (u > 1) {
    for (int i = 1; i < u_l; i++) {
      //if (arr[i] == 0) {
        markMultiples((i+1), u, l);
      //} // if isprime
    } // for (main loop)
  } // u > 1
}

int main() {
  int n;
  std::cin >> n;

  memset(primes, 0, sizeof(primes));

  for (unsigned i = 0; i < n; i++) {
    ll int a[2];
    std::cin >> a[0] >> a[1];
    seive(a[1], a[0]);

    for (int j = 0; j < (a[1] - a[0] + 1); j++) {
      if (primes[j] == 0)
        std::cout << j + a[0] << std::endl;
    }
    std::cout << std::endl;
  }
  return 0;
}
