n = int(input())

ans = 0

while n > 3:
    ans += (n-3)//2 + 3
    n = (n-3+1)//2
    n = (n-3+1)//2

if n > 0:
    ans += n

print(ans)