N = int(input())

lo = 1
hi = 10**400

while lo + 1 < hi:
    mid = (lo + hi) // 2
    if mid*mid < N: lo = mid
    else: hi = mid

print(hi)