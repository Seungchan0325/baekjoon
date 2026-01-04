#include <bits/stdc++.h>

using namespace std;

using ll = __int128_t;

constexpr ll _M = 1e9 + 7;

ll M;

ll getll()
{
    long long x; cin >> x;
    return x;
}

struct Matrix22
{
    ll a00;
    ll a01;
    ll a10;
    ll a11;
};

constexpr Matrix22 Identity = {1, 0, 0, 1};

Matrix22 multiply(const Matrix22& m, const Matrix22& n)
{
    auto [a, b, c, d] = m;
    auto [x, y, p, q] = n;
    return {(a*x+b*p)%M, (a*y+b*q)%M, (c*x+d*p)%M, (c*y+d*q)%M};
}

Matrix22 pw(const Matrix22& x, ll n)
{
    Matrix22 res = Identity;
    Matrix22 base = x;
    while(n) {
        if(n&1) res = multiply(res, base);
        base = multiply(base, base);
        n >>= 1;
    }
    return res;
}

ll pw(ll x, ll n)
{
    ll res = 1;
    ll base = x%M;
    while(n) {
        if(n&1) res = res*base%M;
        base = base*base%M;
        n>>=1;
    }
    return res;
}

constexpr Matrix22 Q = {1, 1, 1, 0};

ll fibo(ll n)
{
    return pw(Q, n).a01;
}

int main()
{
    ll n, k;
    n = getll();
    k = getll();

    M = _M * _M;
    ll f_nk = fibo(n*k);
    ll f_k = fibo(k);
    if(f_k % _M == 0) {
        f_k /= _M;
        f_nk /= _M;
    }
    M = _M;
    ll A = f_nk * pw(f_k, M-2) % M;
    ll B = (fibo(n*k-1) - A * fibo(k-1) % M + M) % M;
    cout << (long long)A << " " << (long long)B << "\n";
}