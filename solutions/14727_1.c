#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define MAXN (100000)
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int top = -1;
int stack_height[MAXN] = {0, };
int stack_count[MAXN] = {0, };

char* p;

int read_int() {
    int ret = 0;
    for(char c = *p++; c & 16; ret = 10 * ret + (c & 15), c = *p++);
    return ret;
}

char buffer[1<<20];

int main(void)
{
    struct stat st; fstat(0, &st);
    p = (char*)mmap(buffer, 1<<20, PROT_READ, MAP_PRIVATE, 0, 0);
    if(p == MAP_FAILED) {
        fprintf(stderr, "can't mmap");
        exit(1);
    }
    int n = read_int();

    long long result = 0;
    for(int i = 0; i < n; i++) {
        int height = read_int();
        int count = 0;
        while(0 <= top && height <= stack_height[top]) {
            count += stack_count[top];
            result = MAX((long long)stack_height[top] * count, result);
            top--;
        }
        top++;
        stack_height[top] = height;
        stack_count[top] = count + 1;
    }

    int count = 0;
    while(0 <= top) {
        count += stack_count[top];
        result = MAX((long long)stack_height[top] * count, result);
        top--;
    }

    printf("%lld", result);
}