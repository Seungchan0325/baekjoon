#include <iostream>

using namespace std;

const int sz = 15;
bool chk[sz];
int n, arr[sz];

int f(int idx) {
    if(idx == n) return 1;
    
    int ret = 0;
    for(int i=0; i<n; i++) {
        if(chk[i]) continue;
        for(int j=0; j<idx; j++) {
            if(arr[j] == j - idx + i || arr[j] == -j + idx + i) {
                goto escape;
            }
        }
        arr[idx] = i;
        chk[i] = true;
        ret += f(idx+1);
        chk[i] = false;
escape: {}
    }
    return ret;
}

int main() {
    cin>>n;
    int result = f(0);
    cout<<result;
}