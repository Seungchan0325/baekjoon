n, m = map(int, input().split())
queue = list(map(int, input().split()))
friends = list(map(int, input().split()))

cnt = 0

for i in queue[m:]:
    if i in friends:
        cnt += 1

print(cnt)