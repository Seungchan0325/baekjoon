#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAXN 101010

int N, H[MAXN];
int top, stack[MAXN];

bool empty()
{
    return top == 0;
}

void push(int x)
{
    stack[top++] = x;
}

int peek()
{
    return stack[top-1];
}

int pop()
{
    return stack[--top];
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) scanf("%d", &H[i]);

    H[0] = -1;
    H[N+1] = -1;
    int ans = 0;
    for(int i = 0; i <= N+1; i++) {
        while(!empty() && H[peek()] > H[i]) {
            int h = H[pop()];
            int w = i - peek() - 1;
            ans = max(h * w, ans);
        }
        push(i);
    }

    printf("%d", ans);
}