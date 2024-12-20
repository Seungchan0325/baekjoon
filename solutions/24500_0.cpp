#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ll N;
    cin >> N;
    int digit = 64 - __builtin_clzll(N);
    ll other = ((1LL<<digit)-1) ^ N;
    if(other == 0) {
        cout << 1 << "\n";
        cout << N << "\n";
    } else {
        assert((N^other) == (1LL<<digit)-1);
        // for(ll i = 0; i < 64; i++) {
        //     if(other&(1LL<<i) && (N^(1LL<<i)) <= N) {
        //         other ^= (1LL<<i);
        //         N ^= (1LL<<i);
        //     }
        // }
        // assert(other < N);
        // assert((N^other) == (1LL<<digit)-1);
        cout << 2 << "\n";
        cout << other << "\n" << N;
    }
}