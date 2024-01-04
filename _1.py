s = input()

sum = 0
cnt = 0

while s:
    cnt += 1
    if s.startswith("A+"):
        s = s[2:]
        sum += 4.5
    elif s.startswith("A"):
        s = s[1:]
        sum += 4
    elif s.startswith("B+"):
        s = s[2:]
        sum += 3.5
    elif s.startswith("B"):
        s = s[1:]
        sum += 3
    elif s.startswith("C+"):
        s = s[2:]
        sum += 2.5
    elif s.startswith("C"):
        s = s[1:]
        sum += 2
    elif s.startswith("D+"):
        s = s[2:]
        sum += 1.5
    elif s.startswith("D"):
        s = s[1:]
        sum += 1
    elif s.startswith("F"):
        s = s[1:]
        sum += 0
        
print(sum / cnt)
Unknown problem. sumbmit number: 66013314