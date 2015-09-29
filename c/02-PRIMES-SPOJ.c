/* NOTE:
 * this file was written by Jamie Wong
 * this file was got from his website: http://jamie-wong.com/2009/11/12/spoj-problem-2-prime-generator/
 *
 * this is commented so that i can get a better understanding of the working
 * of this prime generator.
 *
 * no ill intend to the original author meant.
 */

/* standard headers ?? */
#include <stdio.h> // printf
#include <string.h> // meh, idk? TODO: try removing this ? o.O
#include <stdbool.h> // bool, for simple bool
#include <math.h> // sqrt


/* initial params */
// 1 <= m <= n <= 1000000000
// 1,000,000,000 : 10 ^ 9
// sqrt 10 ^ 9 = 31622.7766017;
//        ceil = 31623

// n - m <= 100000
// 1,00,000 : 10 ^ 5


int main() {
  /* number of primes ??? less than 32000, there are 3432 primes.
   * why is this important? inital seeding? get back to this!!!
   * TODO:!!!
   *
   * TODO: wwhy 4000? guess 4000.
   */
  int primes[4000];
  /* numprimes. being used quite a bit */
  int numprimes = 0;

/* generate all prime numbers till 32000 */
  /* initialize primes[0] to 2, increase nprime */
  primes[numprimes++] = 2;
  for (int i = 3; i <= 32000; i+=2) {
    /* increase by 3's  updto 32000; sqrt 10^9: ~ <32000 */

    bool isprime = true; // initial bool for check

    /* okay, set cap to be sqrt(i) + 1 */
    // i =  3; cap = 2
    // i =  5; cap = 3
    // i =  7; cap = 3
    // i =  9; cap = 4
    // i = 11; cap = 4
    // i = 13; cap = 4
    // i = 15; cap = 4
    // i = 10; cap = 4 // cap ^ 2 > i? why?
    // i = 30; cap = 6 // cap ^ 2 > i? why?
    int cap = sqrt(i)+1; // NOT ceil (sqrt(i) ????????
    //dbg: printf("%d: %d\n", i, cap);

    for (int j = 0; j < numprimes; j++) {
    // this part i do NOT understand, along with lots of others.
    // for j = 0; j < numprimes; j++

    /* primes = [2]
     * for j = 0; j < 1; j++
     *    if primes[j] >= cap; break;
     *
     * if primes[j] >= cap // cap = sqrt(i) + 1
     *    break;
     * why primes[j] >= cap?
     * for every number i, prime factorization of it,
     * least number of prime factor WILL be less than
     * sqrt(i) + 1;
     *
     * eg:
     * 42 = 7 x 3 x 2
     * 49 = 7 x 7
     * 56 = 7 x 2 x 2 x 2
     *
     * thus, if primes[j] go above cap, we can no find more factors
     * so, break;
     */
      if (primes[j] >= cap) break; //<-------------------------------------|
                                                                    //     |
      if (i % primes[j] == 0) {                                     //     |
      /* if (i % primes[j] == 0): i divisible by primes[j]*/        //     |
      /* which means, i is divisible by 1 */                        //     |
      // this relates to above lines, idk how!!!!                   // -----
        isprime = false;
        break;
      }
    }
    // if still prime, add to prime numbers list!!!
    if (isprime) primes[numprimes++] = i;
  }

  //dbg: printf("primes: %d\n", numprimes);
/* generate all prime numbers till 32000 */


  /* start with T, N, M  variables*/
  int T,N,M;

  /* get T */
  scanf("%d",&T);

  for (int t = 0; t < T; t++) {
    /* print new line @ end of every run */
    if (t) printf("\n");

    /* scan two numbers */
    scanf("%d %d",&M,&N);

    /* start with 2?
     * why oh why?
     * no primes less than two
     * should/can we remove this checkfix?
     * FIXME:
     *
     * is M going to affect working of primes? if yes, do not remove
     * this checkfix.
     * */
    if (M < 2) M = 2;

    /* max = sqrt(N) + 1
     * again, max factor that can be is:
     * sqrt(N) + 1
     *
     * */
    int cap = sqrt(N) + 1;

    /* interval: 100000; */
    /*
      * why 100000 + 1 ?
      * for a range of m:n, total number of values
      * are: m - n + 1
      *
      * */
    bool isprime[100001];
    memset(isprime,true,sizeof(isprime)); // set true all

    for (int i = 0; i < numprimes; i++) {
      // W.T.A.F!!?A>>A??
      /* this is where i was.. grr... */

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

  // finally, return 0;
  return 0;
}
