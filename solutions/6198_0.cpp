#include <stdio.h>

#define MAXN 80808
#define INF 1'000'000'007

int N, H[MAXN], stack[MAXN], top, ans;

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

int main()
{
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) scanf("%d", &H[i]);
    H[N+1] = INF;
    for(int i = 1; i <= N+1; i++) {
        while(!empty() && H[peek()] <= H[i]) {
            int j = pop();
            ans += i - j - 1;
        }
        push(i);
    }
    printf("%lld", ans);
}