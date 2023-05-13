import math
from fractions import Fraction 
import random
 

def calculatePower(a, n, mod):
    res = 1
    a = a%mod
    while(n>0):
        if(n & 1):
            res = (res*a)%mod
        n = n>>1
        a = (a*a)%mod
    return res


def KnownDAttack(N, E, D):
    r = E*D-1
    w = random.randint(1, N-1)
    while(r%2==0):
        r = r>>1
    x = math.gcd(w, N)
    if(x>1 and x<N):
        return x
    v = calculatePower(w, r, N)
    if(v%N==1):
        print("UnsucessFull!!!  v = 1")
        return
    w = v 
    while(v%N!=1):
        w = v 
        v = (v*v) % N 
    if(w%N==-1):
        print("UnsucessFull!!!  v = -1")
        return
    print("Successfull!!! ")
    p = math.gcd(w+1, N)
    q = N//p 
    print(f' p = {p} , q = {q}')
    return math.gcd(w+1, n)

if __name__ == "__main__":
    
    # n = 36581
    # e = 4679
    # D = 14039

    n = int(input('Enter N : '))
    e = int(input('Enter E : '))
    D = int(input('Enter D : '))
    KnownDAttack(n, e, D)
    
    