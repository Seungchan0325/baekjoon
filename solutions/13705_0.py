from decimal import *
getcontext().prec = 50
getcontext().rounding = ROUND_HALF_UP

PI = Decimal('3.1415926535897932384626433832795028841971693993751058209')

A, B, C = map(Decimal, input().split())

facts = [Decimal('1')] * 50
for i in range(1, 50):
    facts[i] = facts[i-1] * i

def my_pow(a: Decimal, n: int):
    if n == 0: return Decimal('1')
    if n & 1: return my_pow(a, n-1) * a
    half = my_pow(a, n//2)
    return half * half

def Sin(_x: Decimal) -> Decimal:
    x = _x % (Decimal(2) * PI)
    ret = Decimal('0')

    p = Decimal('1')
    for k in range(20):
        ret += p * (my_pow(x, 2*k+1) / facts[2*k+1])
        p *= Decimal('-1')
    
    return ret

lo = Decimal('0')
hi = Decimal('150005')
for _ in range(300):
    mid = (lo + hi) / 2
    if A * mid + B * Sin(mid) < C: lo = mid
    else: hi = mid

print(round(lo, 6))