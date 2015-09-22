from math import sqrt
from math import ceil

v_max  = 1000000000
c_sqrt = int(ceil(sqrt(v_max)) + 1)

primes = [2];
for i in range(3,32000,2):
    print "i: " + str(i)
    isprime = True

    cap = sqrt(i)+1

    for j in primes:
        print "\tj: " + str(j)
        if (j >= cap):
            print "\t\t"
            break
        if (i % j == 0):
            isprime = False
            break
    if (isprime):
        primes.append(i)

print primes
quit()

n = int(raw_input())
for t in range(0,n):
    m,n = raw_input().split()
    m = int(m)
    n = int(n)
    print m
    print n
