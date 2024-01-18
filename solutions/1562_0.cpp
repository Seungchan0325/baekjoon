#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000000;
int n, cache[100][10][1<<10];

int f(int idx, int prev, int used) {
    if(idx == n) {
        if(used == (1<<10) - 1) return 1;
        else return 0;
    }

    int& ret = cache[idx][prev][used];
    if(ret != -1) return ret;
    
    ret = 0;
    if(0 < prev) {
        ret += f(idx + 1, prev - 1, used | (1<<(prev - 1)));
        ret %= MOD;
    }

    if(prev < 9) {
        ret += f(idx + 1, prev + 1, used | (1<<(prev + 1)));
        ret %= MOD;
    }

    return ret;
}

int main() {
    cin>>n;
    memset(cache, -1, sizeof(cache));
    int result = 0;
    for(int first = 1; first <= 9; first++) {
        result += f(1, first, 1<<first);
        result %= MOD;
    }
    cout<<result;
}