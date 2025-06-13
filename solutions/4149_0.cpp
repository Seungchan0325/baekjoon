#include <bits/stdc++.h>

using namespace std;

using i128 = __int128_t;
using ull = unsigned long long;

ull mul(ull x, ull y, ull mod)
{
    return (i128)x * y % mod;
}

ull pow(ull x, ull n, ull mod)
{
    ull ans = 1;
    ull p = x % mod;
    while(n) {
        if(n&1) ans = mul(ans, p, mod);
        p = mul(p, p, mod);
        n >>= 1;
    }
    return ans;
}

bool miller(ull n, ull a)
{
    if(n % a == 0) return 0;
    ull k = n - 1;
    while(true) {
        ull v = pow(a, k, n);
        if(k&1) return (v != 1 && v != n-1);
        else if(v == n-1) return 0;
        k>>=1;
    }
}

bool isprime(ull n)
{
    for(ull a : { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 }) {
        if(n == a) return true;
        if(n > 40 && miller(n, a)) return false;
    }
    if(n <= 40) return false;
    return true;
}

void factorize(ull n, vector<ull>& v)
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
    ull a, b, c, g = n;
    auto f = [&](ull x) {
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
    ull n;
    cin >> n;
    vector<ull> factors;
    factorize(n, factors);
    sort(factors.begin(), factors.end());
    for(auto i : factors) cout << i << "\n";
}