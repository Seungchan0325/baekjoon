#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll N, P, H;

int main()
{
    cin >> N >> P >> H;

    ll updown = 0;
    for(ll bit = (1LL<<N); bit > 1; bit>>=1) {
        if(H > bit/2) {
            updown |= bit;
            H = bit - H + 1;
        }
    }

    updown >>= 1;

    for(ll bit = (1LL<<(N-1)), i = 0; bit > 0; bit>>=1, i++) {
        if(updown & (1LL<<i)) {
            if(P <= bit) {
                cout << 'L';
                P = bit - P + 1;
            } else {
                cout << 'R';
                P = bit - (P - bit) + 1;
            }
        } else {
            if(P <= bit) {
                cout << 'R';
            } else {
                cout << 'L';
                P -= bit;
            }
        }
    }
}