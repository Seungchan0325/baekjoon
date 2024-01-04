#include <iostream>
int main(void){
    int x, y;
    scanf("%d %d", &x, &y);
    while(x!=0 && y!=0){
        printf("%d\n", x+y);
        
        scanf("%d %d", &x, &y);
    }
}