#include <iostream>
#include <cmath>

using namespace std;

void top(int n, int from, int by, int to){
    cout.tie(NULL);
    if(n==1){
        printf("%d %d\n", from, to);
        return;
    }
    top(n-1, from, to, by);
    printf("%d %d\n", from, to);
    top(n-1, by, from, to);
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    cout<<(1<<n)-1<<endl;
    top(n,1,2,3);
}