#include <iostream>

using namespace std;

const int max_n = 100000;
int n, ans, heights[max_n];
int stack_pointer, stack[max_n];

void print_stack() {
    for(int i=0; i<=stack_pointer; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int main() {
    scanf("%d", &n);
    for(int i=0; i<n; i++) scanf("%d", heights + i);
    
    ans = 0;
    stack_pointer = -1;
    stack[++stack_pointer] = 0;
    for(int i=0; i<=n; i++) {
        while(0 < stack_pointer && heights[i] < heights[stack[stack_pointer]]) {
            int height = heights[stack[stack_pointer--]];
            int width = stack_pointer == 0 ? i : i - stack[stack_pointer] - 1;
            //print_stack();
            ans = max(ans, height * width);
        }
        stack[++stack_pointer] = i;
        //print_stack();
    }

    printf("%d\n", ans);
}