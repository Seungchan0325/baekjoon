#include <iostream>

using namespace std;

int n,trr[15],prr[15],Max;

void f(int idx, int sum, int prev){
    if(idx==n){
        if(Max < sum && prev<=1){
            Max = sum;
        }
        return;
    }

    if(prev == 0){
        if(trr[idx]+idx-1 < n)
            f(idx+1, sum+prr[idx], trr[idx]-1);
        f(idx+1, sum, 0);
    }else{
        f(idx+1, sum, prev-1);
    }
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> trr[i] >> prr[i];
    }
    f(0,0,0);
    cout << Max;
}