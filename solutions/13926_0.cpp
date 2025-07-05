#include <bits/stdc++.h>

using namespace std;

using i128 = __int128_t;
using ll = long long;

ll mul(ll x, ll y, ll mod)
{
    return (i128)x * y % mod;
}

ll pow(ll x, ll n, ll mod)
{
    ll ans = 1;
    ll p = x % mod;
    while(n) {
        if(n&1) ans = mul(ans, p, mod);
        p = mul(p, p, mod);
        n >>= 1;
    }
    return ans;
}

bool miller(ll n, ll a)
{
    if(n % a == 0) return 0;
    ll k = n - 1;
    while(true) {
        ll v = pow(a, k, n);
        if(k&1) return (v != 1 && v != n-1);
        else if(v == n-1) return 0;
        k>>=1;
    }
}

bool isprime(ll n)
{
    for(ll a : { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 }) {
        if(n == a) return true;
        if(n > 40 && miller(n, a)) return false;
    }
    if(n <= 40) return false;
    return true;
}

void factorize(ll n, vector<ll>& v)
{
    if(n == 1) return;
    if(~n&1) {
        v.push_back(2);
        factorize(n/2, v);
        return;
    }
    if(isprime(n)) {
        v.push_back(n);
        return;
    }
    ll a, b, c, g = n;
    auto f = [&](ll x) {
        return (c + (i128)x * x) % n;
    };
    do {
        if(g == n) {
            a = b = rand() % (n - 2) + 2;
            c = rand() % 20 + 1;
        }
        a = f(a);
        b = f(f(b));
        g = gcd(a > b ? a - b : b - a, n);
    } while(g == 1);
    factorize(g, v);
    factorize(n / g, v);
}

int main()
{
    ll n;
    cin >> n;
    vector<ll> factors;
    factorize(n, factors);
    sort(factors.begin(), factors.end());
    factors.erase(unique(factors.begin(), factors.end()), factors.end());
    int k = factors.size();

    ll ans = 0;
    for(unsigned int chosen = 0; chosen < (1<<k); chosen++) {
        int c = popcount(chosen);
        ll m = 1;
        for(int i = 0; i < k; i++)
            if(chosen&(1<<i)) m *= factors[i];
        if(c&1) ans -= n / m;
        else ans += n / m;
    }
    cout << ans;
}