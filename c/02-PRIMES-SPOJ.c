/* NOTE:
 * this file was written by Jamie Wong
 * this file was got from his website: http://jamie-wong.com/2009/11/12/spoj-problem-2-prime-generator/
 *
 * this is commented so that i can get a better understanding of the working
 * of this prime generator.
 *
 * no disrespect to the original author meant.
 */

#include <stdio.h>   // for printf/scanf
#include <string.h>  // for memset
#include <stdbool.h> // for bool
#include <math.h>    // for sqrt

/**
 * question:
 *    Peter wants to generate some prime numbers for his cryptosystem. Help him!
 *    Your task is to generate all prime numbers between two given numbers!
 * input:
 *    the input begins with the number t of test cases in a single line (t<=10).
 *    In each of the next t lines there are two numbers m and n separated
 *    by a space.
 *      1 <= m <= n <= 1000000000;
 *      n-m <= 100000;
 * output:
 *    for every test case print all prime numbers p such that
 *      m <= p <= n,
 *    one number per line. test cases separated by an empty line.
 *
**/

/**
 * pts:
 * 1. all factors of a number n will be less than sqrt(n) + 1
 *    eg:
 *      42 = 7 x 3 x 2
 *      49 = 7 x 7
 *      56 = 7 x 2 x 2 x 2
**/

int main() {
  /**
   * the number of prime numbers less than a particular number, in this case
   * given, sqrt(10 ^ 9), viz. number of primes less than ~32000.
   *
   * TODO: guessing 4000? that's difficult. Refer to Prime-Counting functions.
   *       at any case, the riemann hypothesis is the only function that gives
   *       a reasonable output? (delta ~= 10% in most cases)
   *
   *       since we can't implement that, and preferably pre-processor
   *       directives need to be used, manually calc this first, or use dma,
   *       and/or vectors.
  **/
  int primes[4000];
  int numprimes = 0; // this variable keeps track of total number of primes

  /**
   * generate all prime numbers till 32000
  **/
  primes[numprimes++] = 2; // initialize primes[0] to 2, increase nprime
  for (int i = 3; i <= 32000; i+=2) { // increase from 3 by 2's  upto 32000;
    bool isprime = true; // initial bool for check

    int cap = sqrt(i) + 1;  // since all factors of i will be less than
                            // sqrt(i) + 1 (pt1); use that as a upper cap

    for (int j = 0; j < numprimes; j++) {
      if (primes[j] >= cap) break; // refer to pt1

      if (i % primes[j] == 0) { // i divisible by primes[j]
        isprime = false;
        break;
      } // if (i divisible by primes[j])
    } // for all primes

    if (isprime) primes[numprimes++] = i; // if isprime, primes[] = i
  } // for i = 3 -> 32000; i += 2

  /**
   * generate all prime numbers till 32000 (end)
  **/

  /* start with T, N, M  variables*/
  int T,N,M;

  /* get T */
  scanf("%d",&T);

  for (int t = 0; t < T; t++) {
    if (t) printf("\n"); // refer output;'test cases separated by an empty line'

    scanf("%d %d",&M,&N); //scan two numbers

    /**
     * if we have an M less than 2, we start with 2.
     * why?
     *  a prime is defined as any number greater than n that is divisible by
     *  n and itself.
     * hence, and also makes this easier
    **/
    if (M < 2) M = 2;

    int cap = sqrt(N) + 1; // initialize a cap for N

    bool isprime[100001]; // for a range of m:n, total number of values are:
                          // m - n + 1
    memset(isprime,true,sizeof(isprime)); // set true all

    for (int i = 0; i < numprimes; i++) {
      /* int i = 0; i < numprimes; i++:
       *    go from 0 to numprimes
       *    iterate through primes?
       *    all of primes from 0 to 32000
       */
      int p = primes[i]; // p point to prime at i

      // if p > cap; break;
      // if prime greater than sqrt(N) + 1, we can have no more factors
      // break!
      if(p >= cap) break;


      // int start. now trickery start?
      int start;

      // if p >= M, start = p * 2
      /* wtaf?
       * prime[i] >= M, start = prime[i] * 2;
       * grrr... get back to this later.
       *
       *
       * backnow
       * if P >= M (when we are startin with P, which is prime,)
       * then multiply it by 2;
       * what do we have to do? hop in P's
       * so, if P is >= M, most likely we've missed first multiple of P
       * thus just multiply by 2
       *
       *
       * p >> M so that p * 2 > N?
       * won't happen. why?
       * if(p >= cap) break; line present above.
       */
      if (p >= M) start = p*2;

      /*
       * this is a mystery or so to think
       * M + ((p - M % p) % p)
       * we are adding something to M
       * (p - M % p) % p
       *    order of precedence:
       *    mod > add/sub
       * above expr becomes:
       * (p - (M % p)) % p
       *    M % p = r
       *      M = n * p + r
       * (p - r) % p
       *
       * eg:
       * 7; in 5's
       * 7 % 5 = 2; // (M % p)
       * 5 - 2 = 3; // p - (M % p)
       * 3 % 5 = 3  // (p - r) % p (not necessary? look at next example!)
       *
       * 8 in 8's
       * 8 % 8 = 0; // M % p
       * 8 - 0 = 8; // p - (M % p)
       * 8 % 8 = 0; // (p - r) % p
       *
       * see this is why it's necessary, i guess.
       * if you have 8; then you're missing out M.
       * so, the valid values to add for a number N:
       * assuming block 8
       * filled: 8
       * tofill: 0
       * filled: 7
       * tofill: 1
       * filled: 6
       * tofill: 2
       * filled: 5
       * tofill: 3
       * ...
       *
       * now that that was done, indexes: a PITA!
       */
      else start = M + ((p - M % p) % p);

      //printf("%d\n", 3 % 5);

      /* this looks familiar.
       * j from start, when j <= n; j += p
       * jump in p's from j where j = start
       *
       * so, start must indicate the previous least
       * multiple of P in M:N, hmmm.....????
       * or the starting multiple of P in M:N
       */
      for (int j = start; j <= N; j += p) {
        /* set isprime to false, not prime */
        /* aha, (segmented) sieve of eratothenes */
        // prime hopping!!!
        isprime[j - M] = false;
      } // done marking primes for particular prime p.
    } // for

    // grr, strange code again!!! look out for these :(
    /*
     * if even, M
     * if  odd, M+1
     *
     * WHY!?
     */
    int start = (M % 2)?M:M+1;

    /* checks for two again?
     * if lower = 2, print 2.
     * since, why???
     * TODO: ... ????
     * */
    if (M == 2) {
      printf("2\n");
    }

    /* this is familiar! from start to N, and i += 2 (!?!?!?) */
    for (int i = start; i <= N; i+=2) {
      // if isprime(i - M) print
      if (isprime[i-M]) printf("%d\n",i);
    }

  } // end for T

  return 0;
}
