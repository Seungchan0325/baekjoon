#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int pw(int x, int n, int mod) {
    long long result = 1;
    long long base = x % mod;
    
    while (n > 0) {
        if (n & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        n >>= 1;
    }
    
    return result;
}

struct Barrett {
    uint64_t m;
    __uint128_t im;

    Barrett(uint64_t m) : m(m), im((__uint128_t(1) << 64) / m) {}

    uint64_t reduce(uint64_t a) const {
        __uint128_t q = (__uint128_t(im) * a) >> 64;
        uint64_t r = a - q * m;
        return r < m ? r : r - m;
    }
};

int main()
{
    int n, p;
    cin >> n >> p;

    Barrett bt(p);

    if(2*n <= p) {
        ll f = 1;
        for(int i = 1; i <= n; ++i) {
            f *= i;
            f = bt.reduce(f);
        }
        cout << f << "\n";
    } else {
        ll f = 1;
        for(int i = p-1; i > n; --i) {
            f *= i;
            f = bt.reduce(f);
        }
        ll ans = (ll)pw(f, p-2, p) * (p-1) % p;
        cout << ans << "\n";
    }
}