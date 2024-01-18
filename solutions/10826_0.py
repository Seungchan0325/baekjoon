n = int(input())

x = 0
y = z = 1

for _ in range(n):
    z = x + y
    x = y
    y = z
    
print(x)