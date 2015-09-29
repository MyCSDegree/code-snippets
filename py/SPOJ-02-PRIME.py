from math import sqrt
from math import ceil

primes = [2]
for i in range(3,32000,2):
    isprime = True
    cap = sqrt(i)+1

    for j in primes:
        if (j >= cap):
            break
        if (i % j == 0):
            isprime = False
            break
    if (isprime):
        primes.append(i)

T = input()
output = ""
for t in range(T):
    if (t > 0):
        output += "\n"

    m,n = raw_input().split()
    m = int(m)
    n = int(n)

    cap = sqrt(n) + 1

    if (m < 2):
        m = 2

    isprime = [True] * 100001;

    for p in primes:
        if (p >= cap):
            break

        if (p >= m):
            start = p * 2
        else:
            start = m + ((p - m % p) % p)

        falseblock = [False] * len(isprime[start-m:n+1-m:p]);
        isprime[start-m:n+1-m:p] = falseblock

    for i in range(m, n+1):
        if (isprime[i-m] == True):
            output += str(i) + "\n"

print output[:-1]
