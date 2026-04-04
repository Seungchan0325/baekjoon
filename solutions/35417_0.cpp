#include <cstdint>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2")

#include <bits/stdc++.h>

using namespace std;

int N, T;
uint64_t bs[3125];

void reset(int l, int r)
{
    uint64_t left = ((l&0x3f) == 0 ? 0ull : ((1ull << (l&0x3f)) - 1));
    uint64_t right = ((r&0x3f) == 63 ? 0ull : (~0ull << ((r&0x3f) + 1)));
    if((l>>6) == (r>>6)) {
        bs[l>>6] &= (left | right);
        return;
    }
    for(int i = (l+63)>>6; i < (r>>6); i++) {
        bs[i] = 0;
    }
    bs[l>>6] &= left;
    bs[r>>6] &= right;
}
void or_shift_right()
{
    uint64_t c = 0;
    for(int i = 3124; i >= 0; i--) {
        uint64_t newc = bs[i]&1ull;
        bs[i] |= bs[i] >> 1;
        bs[i] |= c << 63;
        c = newc;
    }
}
void or_shift_left()
{
    uint64_t c = 0;
    for(int i = 0; i < 3125; i++) {
        uint64_t newc = (bs[i]>>63)&1ull;
        bs[i] |= bs[i] << 1;
        bs[i] |= c;
        c = newc;
    }
}
bool test(int x)
{
    return bs[x>>6] & (1ull<<((x&0x3F)));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    cin >> T;
    if(N == 1) {
        int l, r;
        while(T--) cin >> l >> r;
        cout << "0\n";
        return 0;
    }
    bs[0] = 1;
    for(int i = 1; i <= T; i++) {
        or_shift_left();
        or_shift_right();
        if(test(N-1)) {
            cout << i << "\n";
            return 0;
        }
        int l, r;
        cin >> l >> r;
        l--; r--;
        reset(l, r);
    }
    for(int i = N-1; i >= 0; i--) {
        if(test(i)) {
            cout << T + N-i-1 << "\n";
            return 0;
        }
    }
    cout << "-1\n";
}
