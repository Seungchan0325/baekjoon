from decimal import *
from math import gcd

getcontext().prec = 20

n = int(input())
for _ in range(n):
    A, B, C, D = map(Decimal, input().split())
    A, B, C, D = map(lambda x: int(x * 10**11), (A, B, C, D))
    g = gcd(A, B, C, D)
    A //= g
    B //= g
    C //= g
    D //= g

    def f(x):
        return A*x*x*x + B*x*x + C*x + D
    
    def solve(x):
        if f(x) == 0:
            solutions = [Decimal(x)]
            a = Decimal(A)
            b = Decimal(x * A + B)
            c = Decimal(x * x * A + x * B + C)
            D = Decimal(b*b - 4*a*c)
            if D > 0:
                solutions.append((-b - D.sqrt()) / (2*a))
                solutions.append((-b + D.sqrt()) / (2*a))
            elif D == 0:
                solutions.append(-b / (2*a))
            
            solutions.sort()

            prv = Decimal(-1000005)
            for i in solutions:
                if abs(prv - i) > Decimal("1e-10"):
                    print(f"{i:.12f}", end=' ')
                prv = i
            print()
            return True
        return False
    
    for x in range(1000000, -1, -1):
        if solve(x): break
        if solve(-x): break
        