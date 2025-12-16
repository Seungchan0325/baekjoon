#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll mypw(ll x, ll n, ll mod)
{
    x %= mod;
    ll ret = 1;
    while(n) {
        if(n&1) ret *= x, ret %= mod;
        n>>=1;
        x *= x;
        x %= mod;
    }
    return ret;
}

int main()
{
    int a, b, n;
    cin >> a >> b >> n;
    cout << mypw(1ll<<31, n-1, 1e9+7);
}