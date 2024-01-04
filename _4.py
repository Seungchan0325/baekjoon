n, m, k = map(int, input().split())
mi = n
cnt = 0
turning = 0
ans = 0
for i in range(m):
    a, b = map(int, input().split())
    if not turning:
        mi = min(a, mi)
        cnt += b
        if cnt > k:
            ans = i+1
            turning = 1

if turning:
    print(ans, mi)
else:
    print(-1)
Unknown problem. sumbmit number: 58997038