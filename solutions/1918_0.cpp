#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXN 128

int N, top, ans;
char stack[MAXN], S[MAXN];

bool empty()
{
    return top == 0;
}

void push(char x)
{
    stack[top++] = x;
}

char peek()
{
    return stack[top-1];
}

char pop()
{
    return stack[--top];
}

bool is_operator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

int get_priority(char c)
{
    if(c == '(' || c == ')') return 0;
    if(c == '*' || c == '/') return 1;
    if(c == '+' || c == '-') return 2;
    assert(0);
}

int main()
{
    scanf("%s", S);
    N = strlen(S);
    for(int i = 0; i < N; i++) {
        if(!is_operator(S[i])) {
            printf("%c", S[i]);
            continue;
        }
        if(S[i] == ')') {
            while(peek() != '(') {
                printf("%c", pop());
            }
            pop(); // pop '('
        } else {
            while(!empty() && peek() != '(' && get_priority(peek()) <= get_priority(S[i])) {
                printf("%c", pop());
            }
            push(S[i]);
        }
    }
    while(!empty()) {
        printf("%c", pop());
    }
}