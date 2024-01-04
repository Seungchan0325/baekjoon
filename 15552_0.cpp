#include <iostream>
int main(){
    int test_case;
    scanf("%d", &test_case);
    for(int i = 0; i < test_case; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", x+y);
    }
}