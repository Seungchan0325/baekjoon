#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll a, b, c, n, m;

ll f(ll l)
{
    if(a*b <= c) return l;
    ll ret = 0;
    ll n;
    for(n = 1; b*n <= l; n++) {
        if(a*(n-1)*b > c*n) {
            return ret;
        }
        ret += n*c/a - (n-1)*b;
    }
    ll x = (n-1)*b+1;
    while(x <= l) {
        if(a*x <= c*((x+b-1)/b)) ret++;
        x++;
    }
    return ret;
}

int main()
{
    cin >> a >> b >> c;
    cin >> n >> m;
    ll ans = f(m) - f(n-1);
    cout << ans << "\n" << m-n+1-ans;
}