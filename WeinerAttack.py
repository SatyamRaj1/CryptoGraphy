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

def WienerAttack(N, E):
    ContFraction = GenerateContinuedFraction(N, E)
    print(ContFraction)
    for i in range(1, len(ContFraction)+1):
        t = CalcFraction(ContFraction, 1, i)
        # print("Fraction : ", t)
        a = (t.denominator * E) - 1
        b = t.numerator
        if(b==0):
            continue
        if(a%b==0):
            # print("Phi : ", a//b)
            p, q = CalcPQ(a//b, N)
            if(p%1==0 and q%1==0 and p>0 and q>0):
                print("Attack Successfull!!!")
                print(f' p = {p}')
                print(f' q = {q}')
                return

def GenerateContinuedFraction(N, E):
    ContFraction = []
    a = E
    b = N
    while((a%b)!=0):
        ContFraction.append(a//b)
        c = a%b
        a = b
        b = c
    ContFraction.append(a//b)
    return ContFraction

def CalcPQ(Phi, N):
    addi = N - Phi + 1
    subsq = addi**2 - 4*N 
    if(subsq<0):
        return (-1, -1)
    subt = math.sqrt(subsq)
    if(subt%1!=0):
        return (-1, -1)
    return ((addi+subt)/2, (addi-subt)/2)
def CalcFraction(Arr, i, n):
    if(i==n):
        return 0
    return Fraction(1, Arr[i] + CalcFraction(Arr, i+1, n))

if __name__ == "__main__":

    # n = 317940011
    # e = 77537081

    n = int(input('Enter N : '))
    e = int(input('Enter e : '))
    print(f'original p = 12347 , q = 13001')
    WienerAttack(n, e)