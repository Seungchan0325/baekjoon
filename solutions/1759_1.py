from itertools import combinations
l, c = map(int,input().split())
alpha = sorted(list(input().split()))

candidate = list(combinations(alpha,l))

for candi in candidate:
    num_v = 0
    num_c = 0
    for c in candi:
        if c in "aeiou":
            num_v +=1
        else:
            num_c +=1
    
    if num_v >=1 and num_c>=2:
        print(''.join(candi))