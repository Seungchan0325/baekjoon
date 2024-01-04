vowel = "aeiou"

def dfs(result: str, last: int):
    if len(result) == l:
        vowel_cnt = 0

        for i in result:
            for j in vowel:
                if i == j:
                    vowel_cnt += 1
        
        if vowel_cnt < 1 or l - vowel_cnt < 2: return

        print(result)
    
    for i in range(last+1, len(Input)):
        if result[-1] > Input[i]: continue
        dfs(result + Input[i], i)

l, c = map(int, input().split())
Input = list(map(str, input().split()))

Input.sort()

for i in range(len(Input)):
    dfs(Input[i], i)