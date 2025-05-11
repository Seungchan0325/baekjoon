#include <bits/stdc++.h>

using namespace std;

int main()
{
    int a[10] = {};
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            char c; cin >> c;
            if(c == 'O') a[i] |= 1<<j;
        }
    }
    int mask = (1<<10) - 1;
    int ans = 1e9;
    for(int i = 0; i < 1024; i++) {
        int c = 0;
        int b[10];
        int bit = i;
        for(int j = 0; j < 10; j++) b[j] = a[j];
        for(int j = 0; j < 10; j++) {
            c += popcount((unsigned)bit);
            b[j] ^= bit&mask;
            b[j] ^= (bit<<1)&mask;
            b[j] ^= (bit>>1)&mask;
            if(j < 9) b[j+1] ^= bit;
            bit = b[j];
        }
        if(bit == 0) ans = min(ans, c);
    }
    if(ans >= 1e9) cout << -1;
    else cout << ans;
}