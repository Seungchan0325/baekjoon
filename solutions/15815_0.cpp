#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAXN 128

int top, N, stack[MAXN];
char S[MAXN];

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

int operate(char op, int a, int b)
{
    if(op == '+') return a + b;
    if(op == '-') return a - b;
    if(op == '*') return a * b;
    if(op == '/') return a / b;
    assert(0);
}

int main()
{
    scanf("%s", S);
    int N = strlen(S);
    for(int i = 0; i < N; i++) {
        if(isdigit(S[i])) {
            push(S[i] - '0');
            continue;
        }

        int b = pop();
        int a = pop();
        push(operate(S[i], a, b));
    }
    printf("%d", pop());
}