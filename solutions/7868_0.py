p1, p2, p3, i = map(int, input().split())

ham = []
for x in range(60):
    for y in range(60):
        for z in range(60):
            v = p1**x * p2**y * p3 ** z
            if 1 <= v:
                ham.append(v)

ham.sort()
print(ham[i])