#include <iostream>
#include <algorithm>    
using namespace std;
int main(){
    int n, x;
    scanf("%d %d", &n, &x);
    for(int i = 0; i < n; i++){
        int input;
        scanf("%d", &input);
        if(input < x){
            printf("%d ", input);
        }
    }
}